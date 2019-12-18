#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_21__ {scalar_t__ codec_type; scalar_t__ codec_id; int block_align; int sample_rate; scalar_t__ video_delay; scalar_t__ bit_rate; } ;
struct TYPE_20__ {int nb_streams; TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_19__ {int den; int num; } ;
struct TYPE_18__ {int flags; int size_mul; int pts_delta; int stream_id; int size_lsb; void* header_idx; } ;
struct TYPE_17__ {TYPE_4__* frame_code; TYPE_2__* stream; } ;
struct TYPE_16__ {int /*<<< orphan*/ * time_base; } ;
struct TYPE_15__ {int /*<<< orphan*/  avg_frame_rate; TYPE_7__* codecpar; } ;
typedef  TYPE_3__ NUTContext ;
typedef  TYPE_4__ FrameCode ;
typedef  TYPE_5__ AVRational ;
typedef  TYPE_6__ AVFormatContext ;
typedef  TYPE_7__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AV_CODEC_ID_VORBIS ; 
 int FLAG_CODED ; 
 int FLAG_CODED_PTS ; 
 int FLAG_INVALID ; 
 int FLAG_KEY ; 
 int FLAG_SIZE_MSB ; 
 int FLAG_STREAM_ID ; 
 TYPE_5__ av_div_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_get_audio_frame_duration2 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 void* find_header_idx (TYPE_6__*,TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,int) ; 

__attribute__((used)) static void build_frame_code(AVFormatContext *s)
{
    NUTContext *nut = s->priv_data;
    int key_frame, index, pred, stream_id;
    int start = 1;
    int end   = 254;
    int keyframe_0_esc = s->nb_streams > 2;
    int pred_table[10];
    FrameCode *ft;

    ft            = &nut->frame_code[start];
    ft->flags     = FLAG_CODED;
    ft->size_mul  = 1;
    ft->pts_delta = 1;
    start++;

    if (keyframe_0_esc) {
        /* keyframe = 0 escape */
        FrameCode *ft = &nut->frame_code[start];
        ft->flags    = FLAG_STREAM_ID | FLAG_SIZE_MSB | FLAG_CODED_PTS;
        ft->size_mul = 1;
        start++;
    }

    for (stream_id = 0; stream_id < s->nb_streams; stream_id++) {
        int start2 = start + (end - start) * stream_id       / s->nb_streams;
        int end2   = start + (end - start) * (stream_id + 1) / s->nb_streams;
        AVCodecParameters *par        = s->streams[stream_id]->codecpar;
        int is_audio                  = par->codec_type == AVMEDIA_TYPE_AUDIO;
        int intra_only        = /*codec->intra_only || */ is_audio;
        int pred_count;
        int frame_size = 0;

        if (par->codec_type == AVMEDIA_TYPE_AUDIO) {
            frame_size = av_get_audio_frame_duration2(par, 0);
            if (par->codec_id == AV_CODEC_ID_VORBIS && !frame_size)
                frame_size = 64;
        } else {
            AVRational f = av_div_q(av_inv_q(s->streams[stream_id]->avg_frame_rate), *nut->stream[stream_id].time_base);
            if (f.den == 1 && f.num>0)
                frame_size = f.num;
        }
        if (!frame_size)
            frame_size = 1;

        for (key_frame = 0; key_frame < 2; key_frame++) {
            if (!intra_only || !keyframe_0_esc || key_frame != 0) {
                FrameCode *ft = &nut->frame_code[start2];
                ft->flags     = FLAG_KEY * key_frame;
                ft->flags    |= FLAG_SIZE_MSB | FLAG_CODED_PTS;
                ft->stream_id = stream_id;
                ft->size_mul  = 1;
                if (is_audio)
                    ft->header_idx = find_header_idx(s, par, -1, key_frame);
                start2++;
            }
        }

        key_frame = intra_only;
#if 1
        if (is_audio) {
            int frame_bytes;
            int pts;

            if (par->block_align > 0) {
                frame_bytes = par->block_align;
            } else {
                int frame_size = av_get_audio_frame_duration2(par, 0);
                frame_bytes = frame_size * (int64_t)par->bit_rate / (8 * par->sample_rate);
            }

            for (pts = 0; pts < 2; pts++) {
                for (pred = 0; pred < 2; pred++) {
                    FrameCode *ft  = &nut->frame_code[start2];
                    ft->flags      = FLAG_KEY * key_frame;
                    ft->stream_id  = stream_id;
                    ft->size_mul   = frame_bytes + 2;
                    ft->size_lsb   = frame_bytes + pred;
                    ft->pts_delta  = pts * frame_size;
                    ft->header_idx = find_header_idx(s, par, frame_bytes + pred, key_frame);
                    start2++;
                }
            }
        } else {
            FrameCode *ft = &nut->frame_code[start2];
            ft->flags     = FLAG_KEY | FLAG_SIZE_MSB;
            ft->stream_id = stream_id;
            ft->size_mul  = 1;
            ft->pts_delta = frame_size;
            start2++;
        }
#endif

        if (par->video_delay) {
            pred_count    = 5;
            pred_table[0] = -2;
            pred_table[1] = -1;
            pred_table[2] = 1;
            pred_table[3] = 3;
            pred_table[4] = 4;
        } else if (par->codec_id == AV_CODEC_ID_VORBIS) {
            pred_count    = 3;
            pred_table[0] = 2;
            pred_table[1] = 9;
            pred_table[2] = 16;
        } else {
            pred_count    = 1;
            pred_table[0] = 1;
        }

        for (pred = 0; pred < pred_count; pred++) {
            int start3 = start2 + (end2 - start2) * pred / pred_count;
            int end3   = start2 + (end2 - start2) * (pred + 1) / pred_count;

            pred_table[pred] *= frame_size;

            for (index = start3; index < end3; index++) {
                FrameCode *ft = &nut->frame_code[index];
                ft->flags     = FLAG_KEY * key_frame;
                ft->flags    |= FLAG_SIZE_MSB;
                ft->stream_id = stream_id;
//FIXME use single byte size and pred from last
                ft->size_mul  = end3 - start3;
                ft->size_lsb  = index - start3;
                ft->pts_delta = pred_table[pred];
                if (is_audio)
                    ft->header_idx = find_header_idx(s, par, -1, key_frame);
            }
        }
    }
    memmove(&nut->frame_code['N' + 1], &nut->frame_code['N'], sizeof(FrameCode) * (255 - 'N'));
    nut->frame_code[0].flags       =
        nut->frame_code[255].flags =
        nut->frame_code['N'].flags = FLAG_INVALID;
}