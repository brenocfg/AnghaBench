#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct FrameListData {int flags; int sz_alpha; int /*<<< orphan*/  buf_alpha; scalar_t__ have_sse; scalar_t__* sse; int /*<<< orphan*/  pts; int /*<<< orphan*/  buf; int /*<<< orphan*/  sz; } ;
struct TYPE_12__ {int /*<<< orphan*/ * error; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PICTURE_TYPE_I ; 
 int AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_WB64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int VPX_FRAME_IS_KEY ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int ff_alloc_packet2 (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_side_data_set_encoder_stats (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int storeframe(AVCodecContext *avctx, struct FrameListData *cx_frame,
                      AVPacket *pkt)
{
    int ret = ff_alloc_packet2(avctx, pkt, cx_frame->sz, 0);
    uint8_t *side_data;
    if (ret >= 0) {
        int pict_type;
        memcpy(pkt->data, cx_frame->buf, pkt->size);
        pkt->pts = pkt->dts = cx_frame->pts;
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
        avctx->coded_frame->pts       = cx_frame->pts;
        avctx->coded_frame->key_frame = !!(cx_frame->flags & VPX_FRAME_IS_KEY);
FF_ENABLE_DEPRECATION_WARNINGS
#endif

        if (!!(cx_frame->flags & VPX_FRAME_IS_KEY)) {
            pict_type = AV_PICTURE_TYPE_I;
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
            avctx->coded_frame->pict_type = pict_type;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            pkt->flags |= AV_PKT_FLAG_KEY;
        } else {
            pict_type = AV_PICTURE_TYPE_P;
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
            avctx->coded_frame->pict_type = pict_type;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
        }

        ff_side_data_set_encoder_stats(pkt, 0, cx_frame->sse + 1,
                                       cx_frame->have_sse ? 3 : 0, pict_type);

        if (cx_frame->have_sse) {
            int i;
            /* Beware of the Y/U/V/all order! */
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
            avctx->coded_frame->error[0] = cx_frame->sse[1];
            avctx->coded_frame->error[1] = cx_frame->sse[2];
            avctx->coded_frame->error[2] = cx_frame->sse[3];
            avctx->coded_frame->error[3] = 0;    // alpha
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            for (i = 0; i < 3; ++i) {
                avctx->error[i] += cx_frame->sse[i + 1];
            }
            cx_frame->have_sse = 0;
        }
        if (cx_frame->sz_alpha > 0) {
            side_data = av_packet_new_side_data(pkt,
                                                AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL,
                                                cx_frame->sz_alpha + 8);
            if(!side_data) {
                av_packet_unref(pkt);
                av_free(pkt);
                return AVERROR(ENOMEM);
            }
            AV_WB64(side_data, 1);
            memcpy(side_data + 8, cx_frame->buf_alpha, cx_frame->sz_alpha);
        }
    } else {
        return ret;
    }
    return pkt->size;
}