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
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int MAX_SIZE ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ StrCmpi (char*,char*) ; 

bool PackCmpStr(PACK *p, char *name, char *str)
{
	char tmp[MAX_SIZE];

	if (PackGetStr(p, name, tmp, sizeof(tmp)) == false)
	{
		return false;
	}

	if (StrCmpi(tmp, str) == 0)
	{
		return true;
	}

	return false;
}