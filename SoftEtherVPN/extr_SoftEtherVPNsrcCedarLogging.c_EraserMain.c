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
typedef  int /*<<< orphan*/  bs ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int LastFailed; int /*<<< orphan*/  MinFreeSpace; } ;
struct TYPE_8__ {int /*<<< orphan*/  FullPath; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ ERASE_FILE ;
typedef  TYPE_2__ ERASER ;

/* Variables and functions */
 scalar_t__ CheckEraserDiskFreeSpace (TYPE_2__*) ; 
 int /*<<< orphan*/  ELog (TYPE_2__*,char*,char*,...) ; 
 scalar_t__ FileDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeEraseFileList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GenerateEraseFileList (TYPE_2__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ToStrByte (char*,int,int /*<<< orphan*/ ) ; 

void EraserMain(ERASER *e)
{
	LIST *o;
	UINT i;
	bool ok = false;
	char bs[64];
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	// Check the free space first
	if (CheckEraserDiskFreeSpace(e))
	{
		// Vacant enough
		return;
	}

	ToStrByte(bs, sizeof(bs), e->MinFreeSpace);

	// Generate the file list
	o = GenerateEraseFileList(e);

	// Try to delete one by one in order from oldest file
	for (i = 0;i < LIST_NUM(o);i++)
	{
		ERASE_FILE *f = LIST_DATA(o, i);

		// Delete the file
		if (FileDelete(f->FullPath))
		{
			ELog(e, "LE_DELETE", bs, f->FullPath);
		}

		// Check the free space after the deleted
		if (CheckEraserDiskFreeSpace(e))
		{
			// Free space has been restored
			ok = true;
			break;
		}
	}

	// Release the file list
	FreeEraseFileList(o);

	if (e->LastFailed == false && ok == false)
	{
		// Free space is not enough, but can not delete the file any more
		ELog(e, "LE_NOT_ENOUGH_FREE", bs);
	}

	e->LastFailed = ok ? false : true;
}