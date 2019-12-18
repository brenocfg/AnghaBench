#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  ServerListenerList; } ;
typedef  int /*<<< orphan*/  SERVER_LISTENER ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  SiWriteListenerCfg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SiWriteListeners(FOLDER *f, SERVER *s)
{
	// Validate arguments
	if (f == NULL || s == NULL)
	{
		return;
	}

	LockList(s->ServerListenerList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(s->ServerListenerList);i++)
		{
			SERVER_LISTENER *r = LIST_DATA(s->ServerListenerList, i);
			char name[MAX_SIZE];
			Format(name, sizeof(name), "Listener%u", i);
			SiWriteListenerCfg(CfgCreateFolder(f, name), r);
		}
	}
	UnlockList(s->ServerListenerList);
}