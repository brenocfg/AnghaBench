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
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * SiCallTask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void SiCallDeleteSession(SERVER *s, FARM_MEMBER *f, char *hubname, char *session_name)
{
	PACK *p;
	// Validate arguments
	if (s == NULL || f == NULL || hubname == NULL || session_name == NULL)
	{
		return;
	}

	p = NewPack();
	PackAddStr(p, "HubName", hubname);
	PackAddStr(p, "SessionName", session_name);

	p = SiCallTask(f, p, "deletesession");

	FreePack(p);
}