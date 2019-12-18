#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * Parent; int /*<<< orphan*/  Folders; } ;
typedef  TYPE_1__ FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 TYPE_1__* CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgDeleteFolder (TYPE_1__*) ; 
 TYPE_1__* CfgGetFolder (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int CfgReadNextTextBUF (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TAG_ROOT ; 

FOLDER *CfgBufTextToFolder(BUF *b)
{
	FOLDER *f, *c;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	// Read recursively from the root folder
	c = CfgCreateFolder(NULL, "tmp");

	while (true)
	{
		// Read the text stream
		if (CfgReadNextTextBUF(b, c) == false)
		{
			break;
		}
	}

	// Getting root folder
	f = CfgGetFolder(c, TAG_ROOT);
	if (f == NULL)
	{
		// Root folder is not found
		CfgDeleteFolder(c);
		return NULL;
	}

	// Remove the reference from tmp folder to the root
	Delete(c->Folders, f);
	f->Parent = NULL;

	// Delete the tmp folder
	CfgDeleteFolder(c);

	// Return the root folder
	return f;
}