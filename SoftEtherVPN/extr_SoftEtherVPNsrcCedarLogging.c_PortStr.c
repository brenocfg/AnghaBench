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
typedef  int /*<<< orphan*/  tmp ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 char* GetSvcName (int /*<<< orphan*/ *,int,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

char *PortStr(CEDAR *cedar, UINT port, bool udp)
{
	char tmp[MAX_SIZE];
	char *name;
	// Validate arguments
	if (cedar == NULL)
	{
		return NULL;
	}

	name = GetSvcName(cedar, udp, port);

	if (name == NULL)
	{
		snprintf(tmp, sizeof(tmp), "%u", port);
	}
	else
	{
		snprintf(tmp, sizeof(tmp), "%s(%u)", name, port);
	}

	return CopyStr(tmp);
}