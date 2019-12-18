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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  CAPSLIST ;

/* Variables and functions */
 int /*<<< orphan*/  GetCapsInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetServerCaps (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

UINT GetServerCapsInt(SERVER *s, char *name)
{
	CAPSLIST t;
	UINT ret;
	// Validate arguments
	if (s == NULL || name == NULL)
	{
		return 0;
	}

	Zero(&t, sizeof(t));
	GetServerCaps(s, &t);

	ret = GetCapsInt(&t, name);

	return ret;
}