#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_4__ {scalar_t__ vquality; int /*<<< orphan*/  pass_id; scalar_t__ twopass; scalar_t__ indepth_scan; } ;
typedef  TYPE_1__ hb_job_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 scalar_t__ HB_INVALID_VIDEO_QUALITY ; 
 int /*<<< orphan*/  HB_PASS_ENCODE ; 
 int /*<<< orphan*/  HB_PASS_ENCODE_1ST ; 
 int /*<<< orphan*/  HB_PASS_ENCODE_2ND ; 
 int /*<<< orphan*/  HB_PASS_SUBTITLE ; 
 int /*<<< orphan*/  hb_add_internal (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*) ; 

void hb_job_setup_passes(hb_handle_t * h, hb_job_t * job, hb_list_t * list_pass)
{
    if (job->vquality > HB_INVALID_VIDEO_QUALITY)
    {
        job->twopass = 0;
    }
    if (job->indepth_scan)
    {
        hb_deep_log(2, "Adding subtitle scan pass");
        job->pass_id = HB_PASS_SUBTITLE;
        hb_add_internal(h, job, list_pass);
        job->indepth_scan = 0;
    }
    if (job->twopass)
    {
        hb_deep_log(2, "Adding two-pass encode");
        job->pass_id = HB_PASS_ENCODE_1ST;
        hb_add_internal(h, job, list_pass);
        job->pass_id = HB_PASS_ENCODE_2ND;
        hb_add_internal(h, job, list_pass);
    }
    else
    {
        job->pass_id = HB_PASS_ENCODE;
        hb_add_internal(h, job, list_pass);
    }
}