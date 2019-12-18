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
struct TYPE_3__ {int /*<<< orphan*/  DisableDos; int /*<<< orphan*/  Port; int /*<<< orphan*/  Enabled; } ;
typedef  TYPE_1__ SERVER_LISTENER ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void SiWriteListenerCfg(FOLDER *f, SERVER_LISTENER *r)
{
	// Validate arguments
	if (f == NULL || r == NULL)
	{
		return;
	}

	CfgAddBool(f, "Enabled", r->Enabled);
	CfgAddInt(f, "Port", r->Port);
	CfgAddBool(f, "DisableDos", r->DisableDos);
}