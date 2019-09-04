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
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int CfgGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 

UINT CfgGetIp32(FOLDER *f, char *name)
{
	IP p;
	// Validate arguments
	if (f == NULL || name == NULL)
	{
		return 0;
	}

	if (CfgGetIp(f, name, &p) == false)
	{
		return 0;
	}

	return IPToUINT(&p);
}