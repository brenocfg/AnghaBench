#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* f; } ;
struct TYPE_7__ {int stc; int mb_height; int mby; int mbidx; int mb_width; int flags; int /*<<< orphan*/  avctx; int /*<<< orphan*/  pic_structure; TYPE_2__ cur; int /*<<< orphan*/  qp; scalar_t__ qp_fixed; int /*<<< orphan*/  pic_qp_fixed; } ;
struct TYPE_5__ {scalar_t__ pict_type; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVSContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int B_AVAIL ; 
 int C_AVAIL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int decode_slice_header(AVSContext *h, GetBitContext *gb)
{
    if (h->stc > 0xAF)
        av_log(h->avctx, AV_LOG_ERROR, "unexpected start code 0x%02x\n", h->stc);

    if (h->stc >= h->mb_height) {
        av_log(h->avctx, AV_LOG_ERROR, "stc 0x%02x is too large\n", h->stc);
        return AVERROR_INVALIDDATA;
    }

    h->mby   = h->stc;
    h->mbidx = h->mby * h->mb_width;

    /* mark top macroblocks as unavailable */
    h->flags &= ~(B_AVAIL | C_AVAIL);
    if (!h->pic_qp_fixed) {
        h->qp_fixed = get_bits1(gb);
        h->qp       = get_bits(gb, 6);
    }
    /* inter frame or second slice can have weighting params */
    if ((h->cur.f->pict_type != AV_PICTURE_TYPE_I) ||
        (!h->pic_structure && h->mby >= h->mb_width / 2))
        if (get_bits1(gb)) { //slice_weighting_flag
            av_log(h->avctx, AV_LOG_ERROR,
                   "weighted prediction not yet supported\n");
        }
    return 0;
}