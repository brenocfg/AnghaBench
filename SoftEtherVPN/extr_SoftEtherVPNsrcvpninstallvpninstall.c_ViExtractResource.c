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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ * HRSRC ;
typedef  int /*<<< orphan*/ * HINSTANCE ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * FindResourceA (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOAD_LIBRARY_AS_DATAFILE ; 
 int /*<<< orphan*/ * LoadLibraryExA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LoadResource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LockResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

BUF *ViExtractResource(char *exe, char *type, char *name)
{
	HINSTANCE h;
	HRSRC hr;
	HGLOBAL hg;
	UINT size;
	void *data;
	BUF *buf;
	// Validate arguments
	if (exe == NULL || type == NULL || name == NULL)
	{
		return NULL;
	}

	h = LoadLibraryExA(exe, NULL, LOAD_LIBRARY_AS_DATAFILE);
	if (h == NULL)
	{
		return NULL;
	}

	hr = FindResourceA(h, name, type);
	if (hr == NULL)
	{
		FreeLibrary(h);
		return NULL;
	}

	hg = LoadResource(h, hr);
	if (hg == NULL)
	{
		FreeLibrary(h);
		return NULL;
	}

	size = SizeofResource(h, hr);
	data = (void *)LockResource(hg);

	buf = NewBuf();
	WriteBuf(buf, data, size);

	FreeResource(hg);
	FreeLibrary(h);

	SeekBuf(buf, 0, 0);

	return buf;
}