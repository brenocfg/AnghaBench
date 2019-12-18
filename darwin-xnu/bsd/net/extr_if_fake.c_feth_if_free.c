#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/ * if_fake_ref ;
struct TYPE_5__ {int /*<<< orphan*/ * if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  feth_lock () ; 
 int /*<<< orphan*/  feth_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feth_unlock () ; 
 int /*<<< orphan*/ * ifnet_get_if_fake (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_release (TYPE_1__*) ; 

__attribute__((used)) static void 
feth_if_free(ifnet_t ifp)
{
	if_fake_ref		fakeif;

	if (ifp == NULL) {
		return;
	}
	feth_lock();
	fakeif = ifnet_get_if_fake(ifp);
	if (fakeif == NULL) {
		feth_unlock();
		return;
	}
	ifp->if_softc = NULL;
	feth_unlock();
	feth_release(fakeif);
	ifnet_release(ifp);
	return;
}