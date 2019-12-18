#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  IO ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileOpenW (int /*<<< orphan*/ *,int) ; 
 int IsFileExistsW (int /*<<< orphan*/ *) ; 

bool IsFileWriteLockedW(wchar_t *name)
{
	IO *io;
	// Validate arguments
	if (name == NULL)
	{
		return false;
	}

	if (IsFileExistsW(name) == false)
	{
		return false;
	}

	io = FileOpenW(name, true);
	if (io == NULL)
	{
		return true;
	}

	FileClose(io);

	return false;
}