#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {void* pData; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ INSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  HashInstanceName (char*,int,char*) ; 
 int /*<<< orphan*/  HashInstanceNameLocal (char*,int,char*) ; 
 int MAX_SIZE ; 
 void* OSNewSingleInstance (char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

INSTANCE *NewSingleInstanceEx(char *instance_name, bool user_local)
{
	char name[MAX_SIZE];
	INSTANCE *ret;
	void *data;

	if (instance_name != NULL)
	{
		if (user_local == false)
		{
			HashInstanceName(name, sizeof(name), instance_name);
		}
		else
		{
			HashInstanceNameLocal(name, sizeof(name), instance_name);
		}

		data = OSNewSingleInstance(name);
	}
	else
	{
		data = OSNewSingleInstance(NULL);
	}

	if (data == NULL)
	{
		return NULL;
	}

	ret = ZeroMalloc(sizeof(INSTANCE));
	if (instance_name != NULL)
	{
		ret->Name = CopyStr(instance_name);
	}

	ret->pData = data;

	return ret;
}