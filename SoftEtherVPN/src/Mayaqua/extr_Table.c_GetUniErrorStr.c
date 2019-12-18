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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetTableUniStr (char*) ; 
 int MAX_SIZE ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

wchar_t *GetUniErrorStr(UINT err)
{
	wchar_t *ret;
	char name[MAX_SIZE];
	Format(name, sizeof(name), "ERR_%u", err);

	ret = GetTableUniStr(name);
	if (UniStrLen(ret) != 0)
	{
		return ret;
	}
	else
	{
		return _UU("ERR_UNKNOWN");
	}
}