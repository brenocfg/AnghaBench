#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Items; } ;
struct TYPE_8__ {TYPE_2__* Parent; scalar_t__ size; scalar_t__ Type; void* Name; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ ITEM ;
typedef  TYPE_2__ FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Malloc (scalar_t__) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (void*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrLen (char*) ; 
 void* ZeroMalloc (scalar_t__) ; 

ITEM *CfgCreateItem(FOLDER *parent, char *name, UINT type, void *buf, UINT size)
{
	UINT name_size;
	ITEM *t;
#ifdef	CHECK_CFG_NAME_EXISTS
	ITEM tt;
#endif	// CHECK_CFG_NAME_EXISTS
	// Validate arguments
	if (parent == NULL || name == NULL || type == 0 || buf == NULL)
	{
		return NULL;
	}

	name_size = StrLen(name) + 1;

#ifdef	CHECK_CFG_NAME_EXISTS

	// Check whether there are any items with the same name already
	tt.Name = ZeroMalloc(name_size);
	StrCpy(tt.Name, 0, name);
	t = Search(parent->Items, &tt);
	Free(tt.Name);
	if (t != NULL)
	{
		// Duplicated
		return NULL;
	}

#endif	// CHECK_CFG_NAME_EXISTS

	t = ZeroMalloc(sizeof(ITEM));
	t->Buf = Malloc(size);
	Copy(t->Buf, buf, size);
	t->Name = ZeroMalloc(name_size);
	StrCpy(t->Name, 0, name);
	t->Type = type;
	t->size = size;
	t->Parent = parent;
	
	// Add to the parent list 
	Insert(parent->Items, t);

	return t;
}