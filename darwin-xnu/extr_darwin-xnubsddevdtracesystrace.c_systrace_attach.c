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
 int /*<<< orphan*/  DTRACE_PRIV_USER ; 
 int /*<<< orphan*/  S_IFCHR ; 
 scalar_t__ ddi_create_minor_node (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddi_remove_minor_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_probe ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  membar_enter () ; 
 int /*<<< orphan*/  systrace_attr ; 
 int /*<<< orphan*/  systrace_id ; 
 int /*<<< orphan*/  systrace_pops ; 
 void* systrace_probe ; 
 void* systrace_stub ; 

__attribute__((used)) static int
systrace_attach(dev_info_t *devi)
{
	systrace_probe = (void*)&dtrace_probe;
	membar_enter();

	if (ddi_create_minor_node(devi, "systrace", S_IFCHR, 0,
	    DDI_PSEUDO, 0) == DDI_FAILURE ||
	    dtrace_register("syscall", &systrace_attr, DTRACE_PRIV_USER, NULL,
	    &systrace_pops, NULL, &systrace_id) != 0) {
		systrace_probe = systrace_stub;
		ddi_remove_minor_node(devi, NULL);
		return (DDI_FAILURE);
	}

	return (DDI_SUCCESS);
}