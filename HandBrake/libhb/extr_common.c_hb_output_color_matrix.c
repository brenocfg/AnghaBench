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
struct TYPE_3__ {scalar_t__ color_matrix_override; int color_matrix; } ;
typedef  TYPE_1__ hb_job_t ;

/* Variables and functions */
 scalar_t__ HB_COLR_MAT_UNDEF ; 

int hb_output_color_matrix(hb_job_t * job)
{
    if (job->color_matrix_override != HB_COLR_MAT_UNDEF)
        return job->color_matrix_override;
    else
        return job->color_matrix;
}