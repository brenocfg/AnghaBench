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
struct ubc_info {scalar_t__ ui_control; int /*<<< orphan*/  ui_ucred; } ;

/* Variables and functions */
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 scalar_t__ MEMORY_OBJECT_CONTROL_NULL ; 
 int /*<<< orphan*/  cluster_release (struct ubc_info*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_object_control_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  ubc_cs_free (struct ubc_info*) ; 
 int /*<<< orphan*/  ubc_info_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct ubc_info*) ; 

__attribute__((used)) static void
ubc_info_free(struct ubc_info *uip)
{
	if (IS_VALID_CRED(uip->ui_ucred)) {
		kauth_cred_unref(&uip->ui_ucred);
	}

	if (uip->ui_control != MEMORY_OBJECT_CONTROL_NULL)
		memory_object_control_deallocate(uip->ui_control);
	
	cluster_release(uip);
	ubc_cs_free(uip);

	zfree(ubc_info_zone, uip);
	return;
}