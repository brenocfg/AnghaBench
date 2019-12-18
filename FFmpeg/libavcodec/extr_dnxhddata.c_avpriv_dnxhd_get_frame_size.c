#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int frame_size; } ;

/* Variables and functions */
 TYPE_1__* ff_dnxhd_cid_table ; 
 int ff_dnxhd_get_cid_table (int) ; 

int avpriv_dnxhd_get_frame_size(int cid)
{
    int i = ff_dnxhd_get_cid_table(cid);
    if (i<0)
        return i;
    return ff_dnxhd_cid_table[i].frame_size;
}