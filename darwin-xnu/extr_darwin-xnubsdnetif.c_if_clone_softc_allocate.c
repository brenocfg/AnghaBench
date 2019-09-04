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
struct if_clone {int /*<<< orphan*/  ifc_softc_size; int /*<<< orphan*/  ifc_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 void* zalloc (int /*<<< orphan*/ ) ; 

void *
if_clone_softc_allocate(const struct if_clone *ifc)
{
	void *p_clone = NULL;

	VERIFY(ifc != NULL);

	p_clone = zalloc(ifc->ifc_zone);
	if (p_clone != NULL)
		bzero(p_clone, ifc->ifc_softc_size);

	return (p_clone);
}