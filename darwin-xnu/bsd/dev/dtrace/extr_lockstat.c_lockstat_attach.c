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
 int /*<<< orphan*/  DTRACE_PRIV_KERNEL ; 
 int /*<<< orphan*/  S_IFCHR ; 
 scalar_t__ ddi_create_minor_node (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddi_remove_minor_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_probe ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockstat_attr ; 
 int /*<<< orphan*/  lockstat_id ; 
 int /*<<< orphan*/  lockstat_pops ; 
 int /*<<< orphan*/  lockstat_probe ; 
 int /*<<< orphan*/  membar_producer () ; 

__attribute__((used)) static int
lockstat_attach(dev_info_t *devi)
{
	if (ddi_create_minor_node(devi, "lockstat", S_IFCHR, 0,
	    DDI_PSEUDO, 0) == DDI_FAILURE ||
	    dtrace_register("lockstat", &lockstat_attr, DTRACE_PRIV_KERNEL,
	    NULL, &lockstat_pops, NULL, &lockstat_id) != 0) {
		ddi_remove_minor_node(devi, NULL);
		return (DDI_FAILURE);
	}

	lockstat_probe = dtrace_probe;
	membar_producer();

	return (DDI_SUCCESS);
}