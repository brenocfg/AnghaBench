#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_12__ {int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  FileSize; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  Path; } ;
struct TYPE_11__ {size_t NumItem; TYPE_1__* Items; } ;
struct TYPE_10__ {int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  FileSize; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  FilePath; } ;
typedef  TYPE_1__ RPC_ENUM_LOG_FILE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_LOG_FILE ;
typedef  TYPE_3__ LOG_FILE ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  CmpLogFile ; 
 int /*<<< orphan*/  FreeEnumLogFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumLogFile (TYPE_2__*) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 void* ZeroMalloc (int) ; 

void AdjoinRpcEnumLogFile(RPC_ENUM_LOG_FILE *t, RPC_ENUM_LOG_FILE *src)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (t == NULL || src == NULL)
	{
		return;
	}

	o = NewListFast(CmpLogFile);

	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_LOG_FILE_ITEM *e = &t->Items[i];
		LOG_FILE *f = ZeroMalloc(sizeof(LOG_FILE));

		f->FileSize = e->FileSize;
		StrCpy(f->Path, sizeof(f->Path), e->FilePath);
		StrCpy(f->ServerName, sizeof(f->ServerName), e->ServerName);
		f->UpdatedTime = e->UpdatedTime;

		Add(o, f);
	}

	for (i = 0;i < src->NumItem;i++)
	{
		RPC_ENUM_LOG_FILE_ITEM *e = &src->Items[i];
		LOG_FILE *f = ZeroMalloc(sizeof(LOG_FILE));

		f->FileSize = e->FileSize;
		StrCpy(f->Path, sizeof(f->Path), e->FilePath);
		StrCpy(f->ServerName, sizeof(f->ServerName), e->ServerName);
		f->UpdatedTime = e->UpdatedTime;

		Add(o, f);
	}

	FreeRpcEnumLogFile(t);

	Sort(o);

	Zero(t, sizeof(RPC_ENUM_LOG_FILE));
	t->NumItem = LIST_NUM(o);
	t->Items = ZeroMalloc(sizeof(RPC_ENUM_LOG_FILE_ITEM) * t->NumItem);

	for (i = 0;i < t->NumItem;i++)
	{
		LOG_FILE *f = LIST_DATA(o, i);
		RPC_ENUM_LOG_FILE_ITEM *e = &t->Items[i];

		StrCpy(e->FilePath, sizeof(e->FilePath), f->Path);
		StrCpy(e->ServerName, sizeof(e->ServerName), f->ServerName);
		e->FileSize = f->FileSize;
		e->UpdatedTime = f->UpdatedTime;
	}

	FreeEnumLogFile(o);
}