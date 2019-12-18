#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_24__ ;
typedef  struct TYPE_30__   TYPE_21__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {size_t mapping; scalar_t__ blockflag; } ;
typedef  TYPE_1__ vorbis_enc_mode ;
struct TYPE_32__ {size_t* floor; size_t* mux; int coupling_steps; int* magnitude; int* angle; size_t* residue; } ;
typedef  TYPE_2__ vorbis_enc_mapping ;
typedef  int /*<<< orphan*/  vorbis_enc_floor ;
struct TYPE_31__ {int /*<<< orphan*/  remaining_samples; } ;
struct TYPE_30__ {int available; } ;
struct TYPE_33__ {int* log2_blocksize; int channels; float* coeffs; float* floor; TYPE_24__ afq; int /*<<< orphan*/ * residues; int /*<<< orphan*/ * floors; TYPE_2__* mappings; TYPE_1__* modes; scalar_t__ nmodes; TYPE_21__ bufqueue; } ;
typedef  TYPE_3__ vorbis_enc_context ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_36__ {int frame_size; TYPE_3__* priv_data; } ;
struct TYPE_35__ {int size; int duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; } ;
struct TYPE_34__ {int size_in_bits; } ;
typedef  TYPE_4__ PutBitContext ;
typedef  TYPE_5__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_SKIP_SAMPLES ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_FLOOR_VALUES ; 
 int /*<<< orphan*/  apply_window_and_mdct (TYPE_3__*) ; 
 int /*<<< orphan*/ * av_frame_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int ff_af_queue_add (TYPE_24__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ff_af_queue_remove (TYPE_24__*,int,int /*<<< orphan*/ *,int*) ; 
 int ff_alloc_packet2 (TYPE_6__*,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_bufqueue_add (TYPE_6__*,TYPE_21__*,int /*<<< orphan*/ *) ; 
 scalar_t__ floor_encode (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,float*,int) ; 
 int /*<<< orphan*/  floor_fit (TYPE_3__*,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_4__*) ; 
 int ilog (scalar_t__) ; 
 int /*<<< orphan*/  init_put_bits (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  move_audio (TYPE_3__*,int) ; 
 int /*<<< orphan*/  put_bits (TYPE_4__*,int,int) ; 
 int put_bits_count (TYPE_4__*) ; 
 scalar_t__ residue_encode (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,float*,int,int) ; 
 int /*<<< orphan*/ * spawn_empty_frame (TYPE_6__*,int) ; 

__attribute__((used)) static int vorbis_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                               const AVFrame *frame, int *got_packet_ptr)
{
    vorbis_enc_context *venc = avctx->priv_data;
    int i, ret, need_more;
    int frame_size = 1 << (venc->log2_blocksize[1] - 1);
    vorbis_enc_mode *mode;
    vorbis_enc_mapping *mapping;
    PutBitContext pb;

    if (frame) {
        AVFrame *clone;
        if ((ret = ff_af_queue_add(&venc->afq, frame)) < 0)
            return ret;
        clone = av_frame_clone(frame);
        if (!clone)
            return AVERROR(ENOMEM);
        ff_bufqueue_add(avctx, &venc->bufqueue, clone);
    } else
        if (!venc->afq.remaining_samples)
            return 0;

    need_more = venc->bufqueue.available * avctx->frame_size < frame_size;
    need_more = frame && need_more;
    if (need_more)
        return 0;

    /* Pad the bufqueue with empty frames for encoding the last packet. */
    if (!frame) {
        if (venc->bufqueue.available * avctx->frame_size < frame_size) {
            int frames_needed = (frame_size/avctx->frame_size) - venc->bufqueue.available;
            int i;

            for (i = 0; i < frames_needed; i++) {
               AVFrame *empty = spawn_empty_frame(avctx, venc->channels);
               if (!empty)
                   return AVERROR(ENOMEM);

               ff_bufqueue_add(avctx, &venc->bufqueue, empty);
            }
        }
    }

    move_audio(venc, avctx->frame_size);

    if (!apply_window_and_mdct(venc))
        return 0;

    if ((ret = ff_alloc_packet2(avctx, avpkt, 8192, 0)) < 0)
        return ret;

    init_put_bits(&pb, avpkt->data, avpkt->size);

    if (pb.size_in_bits - put_bits_count(&pb) < 1 + ilog(venc->nmodes - 1)) {
        av_log(avctx, AV_LOG_ERROR, "output buffer is too small\n");
        return AVERROR(EINVAL);
    }

    put_bits(&pb, 1, 0); // magic bit

    put_bits(&pb, ilog(venc->nmodes - 1), 1); // Mode for current frame

    mode    = &venc->modes[1];
    mapping = &venc->mappings[mode->mapping];
    if (mode->blockflag) {
        put_bits(&pb, 1, 1); // Previous windowflag
        put_bits(&pb, 1, 1); // Next windowflag
    }

    for (i = 0; i < venc->channels; i++) {
        vorbis_enc_floor *fc = &venc->floors[mapping->floor[mapping->mux[i]]];
        uint16_t posts[MAX_FLOOR_VALUES];
        floor_fit(venc, fc, &venc->coeffs[i * frame_size], posts, frame_size);
        if (floor_encode(venc, fc, &pb, posts, &venc->floor[i * frame_size], frame_size)) {
            av_log(avctx, AV_LOG_ERROR, "output buffer is too small\n");
            return AVERROR(EINVAL);
        }
    }

    for (i = 0; i < venc->channels * frame_size; i++)
        venc->coeffs[i] /= venc->floor[i];

    for (i = 0; i < mapping->coupling_steps; i++) {
        float *mag = venc->coeffs + mapping->magnitude[i] * frame_size;
        float *ang = venc->coeffs + mapping->angle[i]     * frame_size;
        int j;
        for (j = 0; j < frame_size; j++) {
            float a = ang[j];
            ang[j] -= mag[j];
            if (mag[j] > 0)
                ang[j] = -ang[j];
            if (ang[j] < 0)
                mag[j] = a;
        }
    }

    if (residue_encode(venc, &venc->residues[mapping->residue[mapping->mux[0]]],
                       &pb, venc->coeffs, frame_size, venc->channels)) {
        av_log(avctx, AV_LOG_ERROR, "output buffer is too small\n");
        return AVERROR(EINVAL);
    }

    flush_put_bits(&pb);
    avpkt->size = put_bits_count(&pb) >> 3;

    ff_af_queue_remove(&venc->afq, frame_size, &avpkt->pts, &avpkt->duration);

    if (frame_size > avpkt->duration) {
        uint8_t *side = av_packet_new_side_data(avpkt, AV_PKT_DATA_SKIP_SAMPLES, 10);
        if (!side)
            return AVERROR(ENOMEM);
        AV_WL32(&side[4], frame_size - avpkt->duration);
    }

    *got_packet_ptr = 1;
    return 0;
}