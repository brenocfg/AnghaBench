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
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_TRACE_CONSTANT (int,...) ; 
 int /*<<< orphan*/  PMAP__SWITCH ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_number () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  set_dirbase (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splhigh () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

void
pmap_switch(pmap_t tpmap)
{
        spl_t	s;

	PMAP_TRACE_CONSTANT(PMAP_CODE(PMAP__SWITCH) | DBG_FUNC_START, VM_KERNEL_ADDRHIDE(tpmap));
	s = splhigh();		/* Make sure interruptions are disabled */
	set_dirbase(tpmap, current_thread(), cpu_number());
	splx(s);
	PMAP_TRACE_CONSTANT(PMAP_CODE(PMAP__SWITCH) | DBG_FUNC_END);
}