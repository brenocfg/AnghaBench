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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int PackGetIpEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

UINT PackGetIp32Ex(PACK *p, char *name, UINT index)
{
	IP ip;
	// Validate arguments
	if (p == NULL || name == NULL)
	{
		return 0;
	}

	if (PackGetIpEx(p, name, &ip, index) == false)
	{
		return 0;
	}

	return IPToUINT(&ip);
}