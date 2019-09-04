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
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/ * if_fake_ref ;

/* Variables and functions */
 int /*<<< orphan*/  feth_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ feth_is_detaching (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feth_lock () ; 
 int /*<<< orphan*/  feth_set_detaching (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feth_unlock () ; 
 int /*<<< orphan*/  ifnet_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ifnet_get_if_fake (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
feth_clone_destroy(ifnet_t ifp)
{
	if_fake_ref	fakeif;

	feth_lock();
	fakeif = ifnet_get_if_fake(ifp);
	if (fakeif == NULL || feth_is_detaching(fakeif)) {
		feth_unlock();
		return (0);
	}
	feth_set_detaching(fakeif);
	feth_unlock();

	feth_config(ifp, NULL);
	ifnet_detach(ifp);
	return 0;
}