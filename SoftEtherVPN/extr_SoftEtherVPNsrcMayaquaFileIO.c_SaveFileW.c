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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IO ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileCreateW (int /*<<< orphan*/ *) ; 
 int FileWrite (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

bool SaveFileW(wchar_t *name, void *data, UINT size)
{
	IO *io;
	// Validate arguments
	if (name == NULL || (data == NULL && size != 0))
	{
		return false;
	}

	io = FileCreateW(name);
	if (io == NULL)
	{
		return false;
	}

	if (FileWrite(io, data, size) == false)
	{
		FileClose(io);
		return false;
	}

	FileClose(io);

	return true;
}