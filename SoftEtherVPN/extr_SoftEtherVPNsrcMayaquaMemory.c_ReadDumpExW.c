#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {scalar_t__ Current; } ;
typedef  int /*<<< orphan*/  IO ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileOpenExW (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  FileRead (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (void*) ; 
 void* Malloc (int /*<<< orphan*/ ) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 

BUF *ReadDumpExW(wchar_t *filename, bool read_lock)
{
	IO *o;
	BUF *b;
	UINT size;
	void *data;
	// Validate arguments
	if (filename == NULL)
	{
		return NULL;
	}

	o = FileOpenExW(filename, false, read_lock);
	if (o == NULL)
	{
		return NULL;
	}

	size = FileSize(o);
	data = Malloc(size);
	FileRead(o, data, size);
	FileClose(o);

	b = NewBuf();
	WriteBuf(b, data, size);
	b->Current = 0;
	Free(data);

	return b;
}