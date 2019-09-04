#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  name2 ;
struct TYPE_4__ {int WriteMode; int /*<<< orphan*/ * NameW; int /*<<< orphan*/  Name; void* pData; } ;
typedef  TYPE_1__ IO ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertPathW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_IO_CREATE_COUNT ; 
 int MAX_SIZE ; 
 void* OSFileCreateW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

IO *FileCreateInnerW(wchar_t *name)
{
	IO *o;
	void *p;
	wchar_t name2[MAX_SIZE];
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	UniStrCpy(name2, sizeof(name2), name);
	ConvertPathW(name2);

	p = OSFileCreateW(name2);
	if (p == NULL)
	{
		return NULL;
	}

	o = ZeroMalloc(sizeof(IO));
	o->pData = p;
	UniStrCpy(o->NameW, sizeof(o->NameW), name2);
	UniToStr(o->Name, sizeof(o->Name), o->NameW);
	o->WriteMode = true;

	// KS
	KS_INC(KS_IO_CREATE_COUNT);

	return o;
}