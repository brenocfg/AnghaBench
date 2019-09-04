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
typedef  int /*<<< orphan*/  ipc_importance_elem_t ;

/* Variables and functions */
 scalar_t__ IIE_REFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_importance_reference_internal (int /*<<< orphan*/ ) ; 

void
ipc_importance_reference(ipc_importance_elem_t elem)
{
	assert(0 < IIE_REFS(elem));
	ipc_importance_reference_internal(elem);
}