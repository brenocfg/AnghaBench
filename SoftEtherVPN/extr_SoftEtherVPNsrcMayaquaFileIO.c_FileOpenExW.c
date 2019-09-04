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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_6__ {int HamMode; int /*<<< orphan*/ * HamBuf; int /*<<< orphan*/  NameW; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ IO ;

/* Variables and functions */
 TYPE_1__* FileOpenInnerW (int*,int,int) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  InnerFilePathW (int*,int,int*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ReadHamcoreW (int*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  UniToStr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

IO *FileOpenExW(wchar_t *name, bool write_mode, bool read_lock)
{
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	InnerFilePathW(tmp, sizeof(tmp), name);

	if (name[0] == L'|')
	{
		IO *o = ZeroMalloc(sizeof(IO));
		name++;
		UniStrCpy(o->NameW, sizeof(o->NameW), name);
		UniToStr(o->Name, sizeof(o->Name), o->NameW);
		o->HamMode = true;
		o->HamBuf = ReadHamcoreW(name);
		if (o->HamBuf == NULL)
		{
			Free(o);
			return NULL;
		}
		return o;
	}
	else
	{
		return FileOpenInnerW(tmp, write_mode, read_lock);
	}
}