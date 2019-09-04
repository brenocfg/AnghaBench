#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_28__ {int err_recognition; TYPE_1__* priv_data; } ;
struct TYPE_27__ {int key_frame; int /*<<< orphan*/ * data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_26__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_25__ {int got_picture; TYPE_4__* picture_ptr; int /*<<< orphan*/  gb; int /*<<< orphan*/  first_picture; int /*<<< orphan*/  interlaced; } ;
struct TYPE_24__ {int got_sof_data; int picture_index; int has_complete_frame; scalar_t__ got_mxm_bitmask; TYPE_4__** picture; int /*<<< orphan*/  bitmask_size; int /*<<< orphan*/ * mxm_bitmask; TYPE_2__ jpg; } ;
typedef  TYPE_1__ MXpegDecodeContext ;
typedef  TYPE_2__ MJpegDecodeContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int APP0 ; 
 int APP15 ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
#define  COM 134 
#define  DHT 133 
#define  DQT 132 
 int /*<<< orphan*/  EINVAL ; 
#define  EOI 131 
#define  SOF0 130 
#define  SOI 129 
#define  SOS 128 
 int av_frame_ref (void*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ff_mjpeg_decode_dht (TYPE_2__*) ; 
 int ff_mjpeg_decode_dqt (TYPE_2__*) ; 
 int ff_mjpeg_decode_sof (TYPE_2__*) ; 
 int ff_mjpeg_decode_sos (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int ff_mjpeg_find_marker (TYPE_2__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int*) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  mxpeg_check_dimensions (TYPE_1__*,TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mxpeg_decode_app (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int mxpeg_decode_com (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int mxpeg_decode_frame(AVCodecContext *avctx,
                          void *data, int *got_frame,
                          AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    MXpegDecodeContext *s = avctx->priv_data;
    MJpegDecodeContext *jpg = &s->jpg;
    const uint8_t *buf_end, *buf_ptr;
    const uint8_t *unescaped_buf_ptr;
    int unescaped_buf_size;
    int start_code;
    int ret;

    buf_ptr = buf;
    buf_end = buf + buf_size;
    jpg->got_picture = 0;
    s->got_mxm_bitmask = 0;
    while (buf_ptr < buf_end) {
        start_code = ff_mjpeg_find_marker(jpg, &buf_ptr, buf_end,
                                          &unescaped_buf_ptr, &unescaped_buf_size);
        if (start_code < 0)
            goto the_end;
        {
            init_get_bits(&jpg->gb, unescaped_buf_ptr, unescaped_buf_size*8);

            if (start_code >= APP0 && start_code <= APP15) {
                mxpeg_decode_app(s, unescaped_buf_ptr, unescaped_buf_size);
            }

            switch (start_code) {
            case SOI:
                if (jpg->got_picture) //emulating EOI
                    goto the_end;
                break;
            case EOI:
                goto the_end;
            case DQT:
                ret = ff_mjpeg_decode_dqt(jpg);
                if (ret < 0) {
                    av_log(avctx, AV_LOG_ERROR,
                           "quantization table decode error\n");
                    return ret;
                }
                break;
            case DHT:
                ret = ff_mjpeg_decode_dht(jpg);
                if (ret < 0) {
                    av_log(avctx, AV_LOG_ERROR,
                           "huffman table decode error\n");
                    return ret;
                }
                break;
            case COM:
                ret = mxpeg_decode_com(s, unescaped_buf_ptr,
                                       unescaped_buf_size);
                if (ret < 0)
                    return ret;
                break;
            case SOF0:
                s->got_sof_data = 0;
                ret = ff_mjpeg_decode_sof(jpg);
                if (ret < 0) {
                    av_log(avctx, AV_LOG_ERROR,
                           "SOF data decode error\n");
                    return ret;
                }
                if (jpg->interlaced) {
                    av_log(avctx, AV_LOG_ERROR,
                           "Interlaced mode not supported in MxPEG\n");
                    return AVERROR(EINVAL);
                }
                s->got_sof_data = 1;
                break;
            case SOS:
                if (!s->got_sof_data) {
                    av_log(avctx, AV_LOG_WARNING,
                           "Can not process SOS without SOF data, skipping\n");
                    break;
                }
                if (!jpg->got_picture) {
                    if (jpg->first_picture) {
                        av_log(avctx, AV_LOG_WARNING,
                               "First picture has no SOF, skipping\n");
                        break;
                    }
                    if (!s->got_mxm_bitmask){
                        av_log(avctx, AV_LOG_WARNING,
                               "Non-key frame has no MXM, skipping\n");
                        break;
                    }
                    /* use stored SOF data to allocate current picture */
                    av_frame_unref(jpg->picture_ptr);
                    if ((ret = ff_get_buffer(avctx, jpg->picture_ptr,
                                             AV_GET_BUFFER_FLAG_REF)) < 0)
                        return ret;
                    jpg->picture_ptr->pict_type = AV_PICTURE_TYPE_P;
                    jpg->picture_ptr->key_frame = 0;
                    jpg->got_picture = 1;
                } else {
                    jpg->picture_ptr->pict_type = AV_PICTURE_TYPE_I;
                    jpg->picture_ptr->key_frame = 1;
                }

                if (s->got_mxm_bitmask) {
                    AVFrame *reference_ptr = s->picture[s->picture_index ^ 1];
                    if (mxpeg_check_dimensions(s, jpg, reference_ptr) < 0)
                        break;

                    /* allocate dummy reference picture if needed */
                    if (!reference_ptr->data[0] &&
                        (ret = ff_get_buffer(avctx, reference_ptr,
                                             AV_GET_BUFFER_FLAG_REF)) < 0)
                        return ret;

                    ret = ff_mjpeg_decode_sos(jpg, s->mxm_bitmask, s->bitmask_size, reference_ptr);
                    if (ret < 0 && (avctx->err_recognition & AV_EF_EXPLODE))
                        return ret;
                } else {
                    ret = ff_mjpeg_decode_sos(jpg, NULL, 0, NULL);
                    if (ret < 0 && (avctx->err_recognition & AV_EF_EXPLODE))
                        return ret;
                }

                break;
            }

            buf_ptr += (get_bits_count(&jpg->gb)+7) >> 3;
        }

    }

the_end:
    if (jpg->got_picture) {
        int ret = av_frame_ref(data, jpg->picture_ptr);
        if (ret < 0)
            return ret;
        *got_frame = 1;

        s->picture_index ^= 1;
        jpg->picture_ptr = s->picture[s->picture_index];

        if (!s->has_complete_frame) {
            if (!s->got_mxm_bitmask)
                s->has_complete_frame = 1;
            else
                *got_frame = 0;
        }
    }

    return buf_ptr - buf;
}