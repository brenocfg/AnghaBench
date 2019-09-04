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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/ * _UU (char*) ; 

wchar_t *GetServerTypeStr(UINT type)
{
	if (type == SERVER_TYPE_FARM_CONTROLLER)
	{
		return _UU("SM_FARM_CONTROLLER");
	}
	else if (type == SERVER_TYPE_FARM_MEMBER)
	{
		return _UU("SM_FARM_MEMBER");
	}
	return _UU("SM_SERVER_STANDALONE");
}