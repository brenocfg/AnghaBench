#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_10__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  Folders; } ;
struct TYPE_9__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* UniqueToken (TYPE_1__*) ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *CfgEnumFolderToTokenList(FOLDER *f)
{
	TOKEN_LIST *t, *ret;
	UINT i;
	// Validate arguments
	if (f == NULL)
	{
		return NULL;
	}

	t = ZeroMalloc(sizeof(TOKEN_LIST));
	t->NumTokens = LIST_NUM(f->Folders);
	t->Token = ZeroMalloc(sizeof(char *) * t->NumTokens);

	for (i = 0;i < t->NumTokens;i++)
	{
		FOLDER *ff = LIST_DATA(f->Folders, i);
		t->Token[i] = CopyStr(ff->Name);
	}

	ret = UniqueToken(t);
	FreeToken(t);

	return ret;
}