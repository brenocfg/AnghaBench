#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {TYPE_1__* Cedar; } ;
struct TYPE_4__ {scalar_t__ Bridge; } ;
typedef  TYPE_2__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  CEDAR_BETA_SERVER ; 
 int /*<<< orphan*/  CEDAR_BRIDGE_STR ; 
 int /*<<< orphan*/  CEDAR_SERVER_STR ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void GetServerProductNameInternal(SERVER *s, char *name, UINT size)
{
	// Validate arguments
	if (s == NULL || name == NULL)
	{
		return;
	}

#ifdef	BETA_NUMBER
	if (s->Cedar->Bridge)
	{
		StrCpy(name, size, CEDAR_BRIDGE_STR);
	}
	else
	{
		StrCpy(name, size, CEDAR_BETA_SERVER);
	}
	return;
#else	// BETA_NUMBER
	if (s->Cedar->Bridge)
	{
		StrCpy(name, size, CEDAR_BRIDGE_STR);
	}
	else
	{
		StrCpy(name, size, CEDAR_SERVER_STR);
	}
#endif	// BETA_NUMBER
}