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
struct route {int /*<<< orphan*/ * ro_srcia; int /*<<< orphan*/ * ro_lle; int /*<<< orphan*/ * ro_rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_ADDREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLE_ADDREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RT_ADDREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (struct route const*,struct route*,size_t) ; 

void
route_copyout(struct route *dst, const struct route *src, size_t length)
{
	/* Copy everything (rt, srcif, flags, dst) from src */
	bcopy(src, dst, length);

	/* Hold one reference for the local copy of struct route */
	if (dst->ro_rt != NULL)
		RT_ADDREF(dst->ro_rt);

	/* Hold one reference for the local copy of struct lle */
	if (dst->ro_lle != NULL)
		LLE_ADDREF(dst->ro_lle);

	/* Hold one reference for the local copy of struct ifaddr */
	if (dst->ro_srcia != NULL)
		IFA_ADDREF(dst->ro_srcia);
}