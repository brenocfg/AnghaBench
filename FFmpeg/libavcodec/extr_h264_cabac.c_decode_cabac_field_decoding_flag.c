#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* mb_type; } ;
struct TYPE_8__ {int mb_stride; scalar_t__* slice_table; TYPE_1__ cur_pic; } ;
struct TYPE_7__ {int mb_xy; int mb_field_decoding_flag; scalar_t__ slice_num; int /*<<< orphan*/ * cabac_state; int /*<<< orphan*/  cabac; int /*<<< orphan*/  mb_x; } ;
typedef  TYPE_2__ H264SliceContext ;
typedef  TYPE_3__ H264Context ;

/* Variables and functions */
 int get_cabac_noinline (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_cabac_field_decoding_flag(const H264Context *h, H264SliceContext *sl)
{
    const int mbb_xy = sl->mb_xy - 2*h->mb_stride;

    unsigned long ctx = 0;

    ctx += sl->mb_field_decoding_flag & !!sl->mb_x; //for FMO:(s->current_picture.mb_type[mba_xy] >> 7) & (h->slice_table[mba_xy] == h->slice_num);
    ctx += (h->cur_pic.mb_type[mbb_xy] >> 7) & (h->slice_table[mbb_xy] == sl->slice_num);

    return get_cabac_noinline( &sl->cabac, &(sl->cabac_state+70)[ctx] );
}