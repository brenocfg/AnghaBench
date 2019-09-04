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
 void* dtrace_probe ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  machtrace_attr ; 
 int /*<<< orphan*/  machtrace_id ; 
 int /*<<< orphan*/  machtrace_pops ; 
 void* machtrace_probe ; 
 int /*<<< orphan*/  membar_enter () ; 
 int /*<<< orphan*/  systrace_stub ; 

__attribute__((used)) static int
machtrace_attach(dev_info_t *devi)
{
	machtrace_probe = dtrace_probe;
	membar_enter();
	
	if (ddi_create_minor_node(devi, "machtrace", S_IFCHR, 0,
				DDI_PSEUDO, 0) == DDI_FAILURE ||
			dtrace_register("mach_trap", &machtrace_attr, DTRACE_PRIV_USER, NULL,
				&machtrace_pops, NULL, &machtrace_id) != 0) {
                machtrace_probe = (void*)&systrace_stub;
		ddi_remove_minor_node(devi, NULL);
		return (DDI_FAILURE);
	}

	return (DDI_SUCCESS);
}