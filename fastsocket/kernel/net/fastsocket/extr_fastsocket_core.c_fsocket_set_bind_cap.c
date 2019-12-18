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
struct cred {int /*<<< orphan*/  cap_effective; } ;
typedef  int /*<<< orphan*/  kernel_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int /*<<< orphan*/  cap_capget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ current_cred () ; 

__attribute__((used)) static void fsocket_set_bind_cap(kernel_cap_t *p)
{
	kernel_cap_t pE, pI, pP, pN;
	struct cred *new;

	cap_capget(current, &pE, &pI, &pP);
	pN = pE;

	cap_raise(pN, CAP_NET_BIND_SERVICE);

	//TODO: Ugly hack.
	new = (struct cred *)current_cred();
	new->cap_effective = pN;

	*p = pE;
}