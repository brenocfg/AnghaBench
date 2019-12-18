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
typedef  int /*<<< orphan*/  UNIX_VLAN ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * UnixVLanList; int /*<<< orphan*/ * AccountList; int /*<<< orphan*/  CfgRw; } ;
typedef  TYPE_1__ CLIENT ;
typedef  int /*<<< orphan*/  ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeCfgRw (int /*<<< orphan*/ ) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnixVLanFree () ; 

void CiFreeConfiguration(CLIENT *c)
{
	UINT i;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	// Write to the configuration file
	CiSaveConfigurationFile(c);

	// Release the configuration file
	FreeCfgRw(c->CfgRw);

	// Release the account list
	for (i = 0;i < LIST_NUM(c->AccountList);i++)
	{
		ACCOUNT *a = LIST_DATA(c->AccountList, i);

		CiFreeAccount(a);
	}
	ReleaseList(c->AccountList);

	if (c->UnixVLanList != NULL)
	{
		// Release of UNIX version VLAN list
		for (i = 0;i < LIST_NUM(c->UnixVLanList);i++)
		{
			UNIX_VLAN *v = LIST_DATA(c->UnixVLanList, i);
			Free(v);
		}
		ReleaseList(c->UnixVLanList);
	}
	c->UnixVLanList = NULL;

#ifdef	OS_UNIX
	// Release the VLAN
	UnixVLanFree();
#endif	// OS_UNIX
}