#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  get_ue_golomb_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void skip_sub_layer_ordering_info(GetBitContext *gb)
{
    get_ue_golomb_long(gb); // max_dec_pic_buffering_minus1
    get_ue_golomb_long(gb); // max_num_reorder_pics
    get_ue_golomb_long(gb); // max_latency_increase_plus1
}