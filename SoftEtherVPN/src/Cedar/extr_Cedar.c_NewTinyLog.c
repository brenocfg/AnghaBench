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
typedef  int /*<<< orphan*/  name ;
struct TYPE_7__ {int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
struct TYPE_6__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  io; int /*<<< orphan*/  FileName; } ;
typedef  TYPE_1__ TINY_LOG ;
typedef  TYPE_2__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  FileCreate (char*) ; 
 int /*<<< orphan*/  Format (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalTime (TYPE_2__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MakeDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TINY_LOG_DIRNAME ; 
 int /*<<< orphan*/  TINY_LOG_FILENAME ; 
 TYPE_1__* ZeroMalloc (int) ; 

TINY_LOG *NewTinyLog()
{
	char name[MAX_PATH];
	SYSTEMTIME st;
	TINY_LOG *t;

	LocalTime(&st);

	MakeDir(TINY_LOG_DIRNAME);

	Format(name, sizeof(name), TINY_LOG_FILENAME,
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	t = ZeroMalloc(sizeof(TINY_LOG));

	StrCpy(t->FileName, sizeof(t->FileName), name);
	t->io = FileCreate(name);
	t->Lock = NewLock();

	return t;
}