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
struct if_clone {int /*<<< orphan*/  ifc_zone; int /*<<< orphan*/  ifc_softc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,void*) ; 

void
if_clone_softc_deallocate(const struct if_clone *ifc, void *p_softc)
{
	VERIFY(ifc != NULL && p_softc != NULL);
	bzero(p_softc, ifc->ifc_softc_size);
	zfree(ifc->ifc_zone, p_softc);
}