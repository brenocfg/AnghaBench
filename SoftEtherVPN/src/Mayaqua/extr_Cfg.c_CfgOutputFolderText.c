#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_10__ {TYPE_1__* f; int /*<<< orphan*/ * b; scalar_t__ depth; } ;
struct TYPE_9__ {int /*<<< orphan*/  Items; int /*<<< orphan*/  Folders; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ FOLDER ;
typedef  TYPE_2__ CFG_ENUM_PARAM ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddDeclare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CfgAddEnd (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CfgEnumFolder (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CfgEnumFolderProc ; 
 int /*<<< orphan*/  CfgEnumItem (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CfgEnumItemProc ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void CfgOutputFolderText(BUF *b, FOLDER *f, UINT depth)
{
	CFG_ENUM_PARAM p;
	// Validate arguments
	if (b == NULL || f == NULL)
	{
		return;
	}

	// Output starting of the folder
	CfgAddDeclare(b, f->Name, depth);
	depth++;

	Zero(&p, sizeof(CFG_ENUM_PARAM));
	p.depth = depth;
	p.b = b;
	p.f = f;

	// Enumerate the list of items
	CfgEnumItem(f, CfgEnumItemProc, &p);

	if (LIST_NUM(f->Folders) != 0 && LIST_NUM(f->Items) != 0)
	{
		WriteBuf(b, "\r\n", 2);
	}

	// Enumerate the folder list
	CfgEnumFolder(f, CfgEnumFolderProc, &p);
	// Output the end of the folder
	depth--;
	CfgAddEnd(b, depth);

	//WriteBuf(b, "\r\n", 2);
}