#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {scalar_t__ time_increment_bits; TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int FFMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  check_marker (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_new_pred(Mpeg4DecContext *ctx, GetBitContext *gb) {
    MpegEncContext *s = &ctx->m;
    int len = FFMIN(ctx->time_increment_bits + 3, 15);

    get_bits(gb, len);
    if (get_bits1(gb))
        get_bits(gb, len);
    check_marker(s->avctx, gb, "after new_pred");

    return 0;
}