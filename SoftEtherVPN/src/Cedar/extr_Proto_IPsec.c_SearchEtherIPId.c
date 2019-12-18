#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_11__ {int /*<<< orphan*/  Id; } ;
struct TYPE_10__ {int /*<<< orphan*/  LockSettings; int /*<<< orphan*/  EtherIPIdList; } ;
typedef  TYPE_1__ IPSEC_SERVER ;
typedef  TYPE_2__ ETHERIP_ID ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool SearchEtherIPId(IPSEC_SERVER *s, ETHERIP_ID *id, char *id_str)
{
	bool ret = false;
	// Validate arguments
	if (s == NULL || id == NULL || id_str == NULL)
	{
		return false;
	}

	Lock(s->LockSettings);
	{
		ETHERIP_ID t, *k;

		Zero(&t, sizeof(t));

		StrCpy(t.Id, sizeof(t.Id), id_str);

		k = Search(s->EtherIPIdList, &t);

		if (k != NULL)
		{
			Copy(id, k, sizeof(ETHERIP_ID));

			ret = true;
		}
	}
	Unlock(s->LockSettings);

	return ret;
}