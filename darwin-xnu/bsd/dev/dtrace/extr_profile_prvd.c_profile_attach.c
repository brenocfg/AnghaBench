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
typedef  int /*<<< orphan*/  dev_info_t ;

/* Variables and functions */
 scalar_t__ DDI_FAILURE ; 
 int /*<<< orphan*/  DDI_PSEUDO ; 
 int DDI_SUCCESS ; 
 int DTRACE_PRIV_KERNEL ; 
 int DTRACE_PRIV_USER ; 
 int /*<<< orphan*/  PROFILE_MAX_DEFAULT ; 
 int /*<<< orphan*/  S_IFCHR ; 
 scalar_t__ ddi_create_minor_node (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddi_remove_minor_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_attr ; 
 int /*<<< orphan*/  profile_id ; 
 int /*<<< orphan*/  profile_max ; 
 int /*<<< orphan*/  profile_pops ; 

__attribute__((used)) static int
profile_attach(dev_info_t *devi)
{
	if (ddi_create_minor_node(devi, "profile", S_IFCHR, 0,
	    DDI_PSEUDO, 0) == DDI_FAILURE ||
	    dtrace_register("profile", &profile_attr,
	    DTRACE_PRIV_KERNEL | DTRACE_PRIV_USER, NULL,
	    &profile_pops, NULL, &profile_id) != 0) {
		ddi_remove_minor_node(devi, NULL);
		return (DDI_FAILURE);
	}

	profile_max = PROFILE_MAX_DEFAULT;

	return (DDI_SUCCESS);
}