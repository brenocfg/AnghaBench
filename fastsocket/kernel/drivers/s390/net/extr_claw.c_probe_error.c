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
struct claw_privbk {struct claw_privbk* p_mtc_envelope; struct claw_privbk* p_env; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 struct claw_privbk* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct claw_privbk*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
probe_error( struct ccwgroup_device *cgdev)
{
	struct claw_privbk *privptr;

	CLAW_DBF_TEXT(4, trace, "proberr");
	privptr = dev_get_drvdata(&cgdev->dev);
	if (privptr != NULL) {
		dev_set_drvdata(&cgdev->dev, NULL);
		kfree(privptr->p_env);
		kfree(privptr->p_mtc_envelope);
		kfree(privptr);
	}
}