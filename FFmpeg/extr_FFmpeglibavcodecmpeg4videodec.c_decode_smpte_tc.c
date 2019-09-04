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
struct TYPE_5__ {TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  check_marker (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void decode_smpte_tc(Mpeg4DecContext *ctx, GetBitContext *gb)
{
    MpegEncContext *s = &ctx->m;

    skip_bits(gb, 16); /* Time_code[63..48] */
    check_marker(s->avctx, gb, "after Time_code[63..48]");
    skip_bits(gb, 16); /* Time_code[47..32] */
    check_marker(s->avctx, gb, "after Time_code[47..32]");
    skip_bits(gb, 16); /* Time_code[31..16] */
    check_marker(s->avctx, gb, "after Time_code[31..16]");
    skip_bits(gb, 16); /* Time_code[15..0] */
    check_marker(s->avctx, gb, "after Time_code[15..0]");
    skip_bits(gb, 4); /* reserved_bits */
}