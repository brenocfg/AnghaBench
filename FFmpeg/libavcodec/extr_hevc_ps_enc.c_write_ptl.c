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
struct TYPE_5__ {scalar_t__ level_idc; } ;
struct TYPE_4__ {TYPE_2__* sub_layer_ptl; scalar_t__* sub_layer_level_present_flag; scalar_t__* sub_layer_profile_present_flag; TYPE_2__ general_ptl; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ PTL ;

/* Variables and functions */
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  write_ptl_layer (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void write_ptl(PutBitContext *pb, PTL *ptl, int max_num_sub_layers)
{
    int i;

    write_ptl_layer(pb, &ptl->general_ptl);
    put_bits(pb, 8, ptl->general_ptl.level_idc);

    for (i = 0; i < max_num_sub_layers - 1; i++) {
        put_bits(pb, 1, ptl->sub_layer_profile_present_flag[i]);
        put_bits(pb, 1, ptl->sub_layer_level_present_flag[i]);
    }

    if (max_num_sub_layers > 1)
        for (i = max_num_sub_layers - 1; i < 8; i++)
            put_bits(pb, 2, 0); // reserved

    for (i = 0; i < max_num_sub_layers - 1; i++) {
        if (ptl->sub_layer_profile_present_flag[i])
            write_ptl_layer(pb, &ptl->sub_layer_ptl[i]);
        if (ptl->sub_layer_level_present_flag[i])
            put_bits(pb, 8, ptl->sub_layer_ptl[i].level_idc);
    }
}