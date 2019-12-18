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
typedef  size_t UINT ;
struct TYPE_3__ {int /*<<< orphan*/  LinkList; } ;
typedef  int /*<<< orphan*/  LINK ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseLink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void ReleaseAllLink(HUB *h)
{
	LINK **kk;
	UINT num, i;
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	LockList(h->LinkList);
	{
		num = LIST_NUM(h->LinkList);
		kk = ToArray(h->LinkList);
		DeleteAll(h->LinkList);
	}
	UnlockList(h->LinkList);

	for (i = 0;i < num;i++)
	{
		LINK *k = kk[i];

		ReleaseLink(k);
	}

	Free(kk);
}