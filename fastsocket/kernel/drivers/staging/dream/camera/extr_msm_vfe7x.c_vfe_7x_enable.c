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
struct camera_enable_cmd {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EFAULT ; 
 int msm_adsp_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcam_mod ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfe_mod ; 

__attribute__((used)) static int vfe_7x_enable(struct camera_enable_cmd *enable)
{
	int rc = -EFAULT;

	if (!strcmp(enable->name, "QCAMTASK"))
		rc = msm_adsp_enable(qcam_mod);
	else if (!strcmp(enable->name, "VFETASK"))
		rc = msm_adsp_enable(vfe_mod);

	return rc;
}