#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Wmv2Context ;
struct TYPE_3__ {scalar_t__ picture_number; scalar_t__ pict_type; int chroma_qscale; int qscale; int mb_width; int mb_height; int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int FFMIN (int,int) ; 
 int FRAME_SKIPPED ; 
 int SKIP_TYPE_COL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  decode_ext_header (int /*<<< orphan*/ * const) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ show_bits (int /*<<< orphan*/ *,int) ; 

int ff_wmv2_decode_picture_header(MpegEncContext *s)
{
    Wmv2Context *const w = (Wmv2Context *) s;
    int code;

    if (s->picture_number == 0)
        decode_ext_header(w);

    s->pict_type = get_bits1(&s->gb) + 1;
    if (s->pict_type == AV_PICTURE_TYPE_I) {
        code = get_bits(&s->gb, 7);
        av_log(s->avctx, AV_LOG_DEBUG, "I7:%X/\n", code);
    }
    s->chroma_qscale = s->qscale = get_bits(&s->gb, 5);
    if (s->qscale <= 0)
        return AVERROR_INVALIDDATA;

    if (s->pict_type != AV_PICTURE_TYPE_I && show_bits(&s->gb, 1)) {
        GetBitContext gb = s->gb;
        int skip_type = get_bits(&gb, 2);
        int run = skip_type == SKIP_TYPE_COL ? s->mb_width : s->mb_height;

        while (run > 0) {
            int block = FFMIN(run, 25);
            if (get_bits(&gb, block) + 1 != 1<<block)
                break;
            run -= block;
        }
        if (!run)
            return FRAME_SKIPPED;
    }

    return 0;
}