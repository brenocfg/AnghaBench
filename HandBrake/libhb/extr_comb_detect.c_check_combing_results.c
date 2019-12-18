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
struct TYPE_3__ {int comb_check_nthreads; int* block_score; int block_threshold; int mask_box_color; } ;
typedef  TYPE_1__ hb_filter_private_t ;

/* Variables and functions */
 int HB_COMB_HEAVY ; 
 int HB_COMB_LIGHT ; 
 int HB_COMB_NONE ; 

__attribute__((used)) static int check_combing_results( hb_filter_private_t * pv )
{
    int combed = HB_COMB_NONE;

    int ii;
    for (ii = 0; ii < pv->comb_check_nthreads; ii++)
    {
        if (pv->block_score[ii] >= ( pv->block_threshold / 2 ))
        {
            if (pv->block_score[ii] <= pv->block_threshold)
            {
                // Indicate light combing for block_score that is between
                // ( pv->block_threshold / 2 ) and pv->block_threshold
                combed = HB_COMB_LIGHT;
                pv->mask_box_color = 2;
            }
            else if (pv->block_score[ii] > pv->block_threshold)
            {
                pv->mask_box_color = 1;
                return HB_COMB_HEAVY;
            }
        }
    }

    return combed;
}