#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  ledger_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  asid; int /*<<< orphan*/  vasid; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* PMAP_NULL ; 
 int /*<<< orphan*/  PMAP_TRACE (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PMAP__CREATE ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (TYPE_1__*) ; 
 int /*<<< orphan*/  ledger_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_reference (int /*<<< orphan*/ ) ; 
 TYPE_1__* pmap_create_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

pmap_t
pmap_create(
	ledger_t ledger,
	vm_map_size_t size,
	boolean_t is_64bit)
{
	pmap_t pmap;

	PMAP_TRACE(1, PMAP_CODE(PMAP__CREATE) | DBG_FUNC_START, size, is_64bit);

	ledger_reference(ledger);

	pmap = pmap_create_internal(ledger, size, is_64bit);

	if (pmap == PMAP_NULL) {
		ledger_dereference(ledger);
	}

	PMAP_TRACE(1, PMAP_CODE(PMAP__CREATE) | DBG_FUNC_END, VM_KERNEL_ADDRHIDE(pmap), pmap->vasid, pmap->asid);

	return pmap;
}