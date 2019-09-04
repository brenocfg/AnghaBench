#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  d ;
struct TYPE_6__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  size_t UINT ;
struct TYPE_7__ {int /*<<< orphan*/  FileList; } ;
typedef  TYPE_2__ ENUM_DIR_WITH_SUB_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  EnumDirWithSubDirsMain (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  FreeStrList (int /*<<< orphan*/ ) ; 
 char* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniCopyStr (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 void* ZeroMalloc (int) ; 

UNI_TOKEN_LIST *EnumDirWithSubDirsW(wchar_t *dirname)
{
	ENUM_DIR_WITH_SUB_DATA d;
	UNI_TOKEN_LIST *ret;
	UINT i;
	// Validate arguments
	if (dirname == NULL)
	{
		dirname = L"./";
	}

	Zero(&d, sizeof(d));

	d.FileList = NewListFast(NULL);

	EnumDirWithSubDirsMain(&d, dirname);

	ret = ZeroMalloc(sizeof(UNI_TOKEN_LIST));

	ret->NumTokens = LIST_NUM(d.FileList);
	ret->Token = ZeroMalloc(sizeof(wchar_t *) * ret->NumTokens);

	for (i = 0;i < ret->NumTokens;i++)
	{
		wchar_t *s = LIST_DATA(d.FileList, i);

		ret->Token[i] = UniCopyStr(s);
	}

	FreeStrList(d.FileList);

	return ret;
}