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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  int /*<<< orphan*/  ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/ * PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ELEMENT *PackAddIp6AddrEx(PACK *p, char *name, IPV6_ADDR *addr, UINT index, UINT total)
{
	// Validate arguments
	if (p == NULL || name == NULL || addr == NULL)
	{
		return NULL;
	}

	return PackAddDataEx(p, name, addr, sizeof(IPV6_ADDR), index, total);
}