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
typedef  int /*<<< orphan*/  zoneid_t ;
typedef  int /*<<< orphan*/  jailid ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

zoneid_t
getzoneid(void)
{
	size_t size;
	int jailid;

	/* Information that we are in jail or not is enough for our needs. */
	size = sizeof(jailid);
	if (sysctlbyname("security.jail.jailed", &jailid, &size, NULL, 0) == -1)
		assert(!"No security.jail.jailed sysctl!");
	return ((zoneid_t)jailid);
}