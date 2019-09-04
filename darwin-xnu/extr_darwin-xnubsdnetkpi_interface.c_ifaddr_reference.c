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
typedef  int /*<<< orphan*/ * ifaddr_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IFA_ADDREF (int /*<<< orphan*/ *) ; 

errno_t
ifaddr_reference(ifaddr_t ifa)
{
	if (ifa == NULL)
		return (EINVAL);

	IFA_ADDREF(ifa);
	return (0);
}