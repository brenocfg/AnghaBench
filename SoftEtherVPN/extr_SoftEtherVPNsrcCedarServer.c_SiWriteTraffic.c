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
struct TYPE_3__ {int /*<<< orphan*/  Recv; int /*<<< orphan*/  Send; } ;
typedef  TYPE_1__ TRAFFIC ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SiWriteTrafficInner (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

void SiWriteTraffic(FOLDER *parent, char *name, TRAFFIC *t)
{
	FOLDER *f;
	// Validate arguments
	if (parent == NULL || name == NULL || t == NULL)
	{
		return;
	}

	f = CfgCreateFolder(parent, name);

	SiWriteTrafficInner(f, "SendTraffic", &t->Send);
	SiWriteTrafficInner(f, "RecvTraffic", &t->Recv);
}