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
struct TYPE_3__ {int cid; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* ff_dnxhd_cid_table ; 

int ff_dnxhd_get_cid_table(int cid)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(ff_dnxhd_cid_table); i++)
        if (ff_dnxhd_cid_table[i].cid == cid)
            return i;
    return -1;
}