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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  IO ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CalcUtf8ToUni (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileOpen (char*,int) ; 
 int /*<<< orphan*/  FileRead (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 scalar_t__ FileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 scalar_t__ Malloc (scalar_t__) ; 
 int /*<<< orphan*/  Utf8ToUni (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ZeroMalloc (scalar_t__) ; 

__attribute__((used)) static wchar_t *WuUniReadFile(char *filename)
{
	IO *io;
	UINT size, usize;
	BYTE *utf8;
	wchar_t *wchars;

	// Validate arguments
	if (filename == NULL)
	{
		return NULL;
	}

	io = FileOpen(filename, false);
	if (io == NULL)
	{
		return NULL;
	}

	// Load the file
	size = FileSize(io);
	utf8 = (BYTE*)Malloc(size);
	FileRead(io, (void*)utf8, size);
	FileClose(io);

	usize = CalcUtf8ToUni(utf8, size);
	wchars = (wchar_t*)ZeroMalloc(usize+sizeof(wchar_t));
	Utf8ToUni(wchars, usize, utf8, size);
	Free(utf8);

	return wchars;
}