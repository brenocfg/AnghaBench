#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  Folders; } ;
typedef  TYPE_1__ FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  ZeroMalloc (scalar_t__) ; 

FOLDER *CfgFindFolder(FOLDER *parent, char *name)
{
	FOLDER *f, ff;
	// Validate arguments
	if (parent == NULL || name == NULL)
	{
		return NULL;
	}

	ff.Name = ZeroMalloc(StrLen(name) + 1);
	StrCpy(ff.Name, 0, name);
	f = Search(parent->Folders, &ff);
	Free(ff.Name);

	return f;
}