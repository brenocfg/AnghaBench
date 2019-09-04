#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int UINT ;
struct TYPE_7__ {int NumItem; TYPE_1__** Items; } ;
struct TYPE_6__ {int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_VLAN ;
typedef  int /*<<< orphan*/  REMOTE_CLIENT ;

/* Variables and functions */
 scalar_t__ CcEnumVLan (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CiFreeClientEnumVLan (TYPE_2__*) ; 
 int /*<<< orphan*/  CiGenerateVLanRegulatedName (char*,int,int) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int MAX_SIZE ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool CiGetNextRecommendedVLanName(REMOTE_CLIENT *r, char *name, UINT size)
{
	RPC_CLIENT_ENUM_VLAN t;
	UINT i;
	bool b;
	UINT j;
	bool ok = false;
	// Validate arguments
	if (r == NULL || name == NULL)
	{
		return false;
	}

	Zero(&t, sizeof(t));

	if (CcEnumVLan(r, &t) != ERR_NO_ERROR)
	{
		return false;
	}

	for (i = 1;i < 128;i++)
	{
		char tmp[MAX_SIZE];

		CiGenerateVLanRegulatedName(tmp, sizeof(tmp), i);

		b = false;

		for (j = 0;j < t.NumItem;j++)
		{
			if (StrCmpi(t.Items[j]->DeviceName, tmp) == 0)
			{
				b = true;
				break;
			}
		}

		if (b == false)
		{
			ok = true;

			StrCpy(name, size, tmp);
			break;
		}
	}

	if (ok)
	{
		CiFreeClientEnumVLan(&t);
	}

	return true;
}