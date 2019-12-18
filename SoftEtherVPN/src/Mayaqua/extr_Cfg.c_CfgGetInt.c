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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {scalar_t__ Type; int size; scalar_t__ Buf; } ;
typedef  TYPE_1__ ITEM ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 TYPE_1__* CfgFindItem (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ITEM_TYPE_INT ; 

UINT CfgGetInt(FOLDER *f, char *name)
{
	ITEM *t;
	UINT *ret;
	// Validate arguments
	if (f == NULL || name == NULL)
	{
		return 0;
	}

	t = CfgFindItem(f, name);
	if (t == NULL)
	{
		return 0;
	}
	if (t->Type != ITEM_TYPE_INT)
	{
		return 0;
	}
	if (t->size != sizeof(UINT))
	{
		return 0;
	}

	ret = (UINT *)t->Buf;
	return *ret;
}