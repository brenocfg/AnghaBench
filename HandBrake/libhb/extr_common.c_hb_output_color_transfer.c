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
struct TYPE_3__ {scalar_t__ color_transfer_override; int color_transfer; } ;
typedef  TYPE_1__ hb_job_t ;

/* Variables and functions */
 scalar_t__ HB_COLR_TRA_UNDEF ; 

int hb_output_color_transfer(hb_job_t * job)
{
    if (job->color_transfer_override != HB_COLR_TRA_UNDEF)
        return job->color_transfer_override;
    else
        return job->color_transfer;
}