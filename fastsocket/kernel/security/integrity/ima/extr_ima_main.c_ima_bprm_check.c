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
struct linux_binprm {int /*<<< orphan*/  filename; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPRM_CHECK ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  ima_enabled ; 
 int process_measurement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ima_bprm_check(struct linux_binprm *bprm)
{
	int rc;

	if (!ima_enabled)
		return 0;

	rc = process_measurement(bprm->file, bprm->filename,
				 MAY_EXEC, BPRM_CHECK);
	return 0;
}