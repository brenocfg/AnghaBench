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
struct if_clone {scalar_t__ ifc_softc_size; int /*<<< orphan*/  ifc_mutex; int /*<<< orphan*/  ifc_zone; int /*<<< orphan*/  ifc_units; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct if_clone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_CLONE ; 
 int /*<<< orphan*/  if_cloners_count ; 
 int /*<<< orphan*/  ifc_list ; 
 int /*<<< orphan*/  ifnet_lock_group ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zdestroy (int /*<<< orphan*/ ) ; 

void
if_clone_detach(struct if_clone *ifc)
{
	LIST_REMOVE(ifc, ifc_list);
	FREE(ifc->ifc_units, M_CLONE);
	if (ifc->ifc_softc_size != 0)
		zdestroy(ifc->ifc_zone);

	lck_mtx_destroy(&ifc->ifc_mutex, ifnet_lock_group);
	if_cloners_count--;
}