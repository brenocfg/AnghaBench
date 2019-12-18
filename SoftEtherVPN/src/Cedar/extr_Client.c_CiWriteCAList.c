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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  CaList; } ;
struct TYPE_5__ {TYPE_2__* Cedar; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CiWriteCACert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void CiWriteCAList(CLIENT *c, FOLDER *f)
{
	CEDAR *cedar;
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	cedar = c->Cedar;

	LockList(cedar->CaList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(cedar->CaList);i++)
		{
			char tmp[MAX_SIZE];
			X *x = LIST_DATA(cedar->CaList, i);
			Format(tmp, sizeof(tmp), "Certificate%u", i);
			CiWriteCACert(c, CfgCreateFolder(f, tmp), x);
		}
	}
	UnlockList(cedar->CaList);
}