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
typedef  int /*<<< orphan*/  hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_job_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_MODE_HE ; 
 int encCoreAudioInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int encCoreAudioInitHE(hb_work_object_t *w, hb_job_t *job)
{
    return encCoreAudioInit(w, job, AAC_MODE_HE);
}