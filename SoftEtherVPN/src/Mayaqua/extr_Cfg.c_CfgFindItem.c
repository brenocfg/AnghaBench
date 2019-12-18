#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Items; } ;
struct TYPE_7__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ ITEM ;
typedef  TYPE_2__ FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  ZeroMalloc (scalar_t__) ; 

ITEM *CfgFindItem(FOLDER *parent, char *name)
{
	ITEM *t, tt;
	// Validate arguments
	if (parent == NULL || name == NULL)
	{
		return NULL;
	}

	tt.Name = ZeroMalloc(StrLen(name) + 1);
	StrCpy(tt.Name, 0, name);
	t = Search(parent->Items, &tt);
	Free(tt.Name);

	return t;
}