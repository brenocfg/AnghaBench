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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* GetTableStr (char*) ; 
 int MAX_SIZE ; 
 scalar_t__ StrLen (char*) ; 
 char* _SS (char*) ; 

char *GetErrorStr(UINT err)
{
	char *ret;
	char name[MAX_SIZE];
	Format(name, sizeof(name), "ERR_%u", err);

	ret = GetTableStr(name);
	if (StrLen(ret) != 0)
	{
		return ret;
	}
	else
	{
		return _SS("ERR_UNKNOWN");
	}
}