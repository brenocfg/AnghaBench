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
struct TYPE_4__ {void* UnicastBytes; void* UnicastCount; void* BroadcastBytes; void* BroadcastCount; } ;
typedef  TYPE_1__ TRAFFIC_ENTRY ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void SiLoadTrafficInner(FOLDER *parent, char *name, TRAFFIC_ENTRY *e)
{
	FOLDER *f;
	// Validate arguments
	if (e != NULL)
	{
		Zero(e, sizeof(TRAFFIC_ENTRY));
	}
	if (parent == NULL || name == NULL || e == NULL)
	{
		return;
	}

	f = CfgGetFolder(parent, name);
	if (f == NULL)
	{
		return;
	}

	e->BroadcastCount = CfgGetInt64(f, "BroadcastCount");
	e->BroadcastBytes = CfgGetInt64(f, "BroadcastBytes");
	e->UnicastCount = CfgGetInt64(f, "UnicastCount");
	e->UnicastBytes = CfgGetInt64(f, "UnicastBytes");
}