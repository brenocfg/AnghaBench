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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SiAddListenerEx (int /*<<< orphan*/ *,scalar_t__,int,int) ; 

void SiLoadListenerCfg(SERVER *s, FOLDER *f)
{
	bool enable;
	UINT port;
	bool disable_dos;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

	enable = CfgGetBool(f, "Enabled");
	port = CfgGetInt(f, "Port");
	disable_dos = CfgGetBool(f, "DisableDos");

	if (port == 0)
	{
		return;
	}

	SiAddListenerEx(s, port, enable, disable_dos);
}