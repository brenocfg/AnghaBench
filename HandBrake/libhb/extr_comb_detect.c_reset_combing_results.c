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
struct TYPE_3__ {int comb_check_nthreads; scalar_t__* block_score; scalar_t__ comb_check_complete; } ;
typedef  TYPE_1__ hb_filter_private_t ;

/* Variables and functions */

__attribute__((used)) static void reset_combing_results( hb_filter_private_t * pv )
{
    pv->comb_check_complete = 0;
    int ii;
    for (ii = 0; ii < pv->comb_check_nthreads; ii++)
    {
       pv->block_score[ii] = 0;
    }
}