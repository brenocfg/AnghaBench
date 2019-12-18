#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;
struct TYPE_6__ {size_t NumItem; TYPE_1__** Items; } ;
struct TYPE_5__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_ACCOUNT ;
typedef  int /*<<< orphan*/  REMOTE_CLIENT ;

/* Variables and functions */
 scalar_t__ CcEnumAccount (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CiFreeClientEnumAccount (TYPE_2__*) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int MAX_SIZE ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniTrim (int /*<<< orphan*/ *) ; 

bool CmdIsAccountName(REMOTE_CLIENT *r, wchar_t *name)
{
	UINT i;
	RPC_CLIENT_ENUM_ACCOUNT t;
	wchar_t tmp[MAX_SIZE];
	bool b = false;
	// Validate arguments
	if (r == NULL || name == NULL)
	{
		return false;
	}

	if (CcEnumAccount(r, &t) != ERR_NO_ERROR)
	{
		return false;
	}

	UniStrCpy(tmp, sizeof(tmp), name);
	UniTrim(tmp);

	for (i = 0;i < t.NumItem;i++)
	{
		if (UniStrCmpi(t.Items[i]->AccountName, tmp) == 0)
		{
			b = true;
			break;
		}
	}

	CiFreeClientEnumAccount(&t);

	return b;
}