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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ Type; scalar_t__ size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ ITEM ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 TYPE_1__* CfgFindItem (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ITEM_TYPE_BYTE ; 

UINT CfgGetByte(FOLDER *f, char *name, void *buf, UINT size)
{
	ITEM *t;
	// Validate arguments
	if (f == NULL || name == NULL || buf == NULL)
	{
		return 0;
	}

	t = CfgFindItem(f, name);
	if (t == NULL)
	{
		return 0;
	}
	if (t->Type != ITEM_TYPE_BYTE)
	{
		return 0;
	}
	if (t->size <= size)
	{
		Copy(buf, t->Buf, t->size);
		return t->size;
	}
	else
	{
		Copy(buf, t->Buf, size);
		return t->size;
	}
}