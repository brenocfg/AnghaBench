#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {int debug; } ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {void* closed_gop; TYPE_5__* avctx; int /*<<< orphan*/  gb; int /*<<< orphan*/  timecode_frame_start; } ;
struct TYPE_7__ {TYPE_1__ mpeg_enc_ctx; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg1Context ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int AV_TIMECODE_STR_SIZE ; 
 int FF_DEBUG_PICT_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,char*,void*,int) ; 
 int /*<<< orphan*/  av_timecode_make_mpeg_tc_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void mpeg_decode_gop(AVCodecContext *avctx,
                            const uint8_t *buf, int buf_size)
{
    Mpeg1Context *s1  = avctx->priv_data;
    MpegEncContext *s = &s1->mpeg_enc_ctx;
    int broken_link;
    int64_t tc;

    init_get_bits(&s->gb, buf, buf_size * 8);

    tc = s-> timecode_frame_start = get_bits(&s->gb, 25);

#if FF_API_PRIVATE_OPT
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->timecode_frame_start = tc;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    s->closed_gop = get_bits1(&s->gb);
    /* broken_link indicates that after editing the
     * reference frames of the first B-Frames after GOP I-Frame
     * are missing (open gop) */
    broken_link = get_bits1(&s->gb);

    if (s->avctx->debug & FF_DEBUG_PICT_INFO) {
        char tcbuf[AV_TIMECODE_STR_SIZE];
        av_timecode_make_mpeg_tc_string(tcbuf, tc);
        av_log(s->avctx, AV_LOG_DEBUG,
               "GOP (%s) closed_gop=%d broken_link=%d\n",
               tcbuf, s->closed_gop, broken_link);
    }
}