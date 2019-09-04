#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int bit_rate; int loop_filter; int slice_height; int mb_height; TYPE_2__* avctx; } ;
struct TYPE_8__ {int mspel_bit; int abt_flag; int j_type_bit; int top_left_mv_flag; int per_mb_rl_bit; TYPE_4__ s; } ;
typedef  TYPE_3__ Wmv2Context ;
struct TYPE_6__ {int den; int num; } ;
struct TYPE_7__ {TYPE_1__ time_base; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int encode_ext_header(Wmv2Context *w)
{
    MpegEncContext *const s = &w->s;
    PutBitContext pb;
    int code;

    init_put_bits(&pb, s->avctx->extradata, s->avctx->extradata_size);

    put_bits(&pb, 5, s->avctx->time_base.den / s->avctx->time_base.num); // yes 29.97 -> 29
    put_bits(&pb, 11, FFMIN(s->bit_rate / 1024, 2047));

    put_bits(&pb, 1, w->mspel_bit        = 1);
    put_bits(&pb, 1, s->loop_filter);
    put_bits(&pb, 1, w->abt_flag         = 1);
    put_bits(&pb, 1, w->j_type_bit       = 1);
    put_bits(&pb, 1, w->top_left_mv_flag = 0);
    put_bits(&pb, 1, w->per_mb_rl_bit    = 1);
    put_bits(&pb, 3, code                = 1);

    flush_put_bits(&pb);

    s->slice_height = s->mb_height / code;

    return 0;
}