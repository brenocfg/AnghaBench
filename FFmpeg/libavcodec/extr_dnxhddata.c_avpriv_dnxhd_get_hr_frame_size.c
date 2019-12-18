#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {int den; scalar_t__ num; } ;
struct TYPE_4__ {TYPE_1__ packet_scale; } ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 TYPE_2__* ff_dnxhd_cid_table ; 
 int ff_dnxhd_get_cid_table (int) ; 

int avpriv_dnxhd_get_hr_frame_size(int cid, int w, int h)
{
    int result, i = ff_dnxhd_get_cid_table(cid);

    if (i < 0)
        return i;

    result = ((h + 15) / 16) * ((w + 15) / 16) * (int64_t)ff_dnxhd_cid_table[i].packet_scale.num / ff_dnxhd_cid_table[i].packet_scale.den;
    result = (result + 2048) / 4096 * 4096;

    return FFMAX(result, 8192);
}