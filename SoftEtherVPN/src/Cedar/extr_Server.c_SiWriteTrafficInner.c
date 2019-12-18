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
struct TYPE_3__ {int /*<<< orphan*/  UnicastBytes; int /*<<< orphan*/  UnicastCount; int /*<<< orphan*/  BroadcastBytes; int /*<<< orphan*/  BroadcastCount; } ;
typedef  TYPE_1__ TRAFFIC_ENTRY ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 

void SiWriteTrafficInner(FOLDER *parent, char *name, TRAFFIC_ENTRY *e)
{
	FOLDER *f;
	// Validate arguments
	if (parent == NULL || name == NULL || e == NULL)
	{
		return;
	}

	f = CfgCreateFolder(parent, name);
	CfgAddInt64(f, "BroadcastCount", e->BroadcastCount);
	CfgAddInt64(f, "BroadcastBytes", e->BroadcastBytes);
	CfgAddInt64(f, "UnicastCount", e->UnicastCount);
	CfgAddInt64(f, "UnicastBytes", e->UnicastBytes);
}