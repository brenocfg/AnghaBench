#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dt ;
struct TYPE_8__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  io; } ;
typedef  TYPE_1__ TINY_LOG ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  GetDateTimeStrMilli64 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalTime64 () ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,char*,int) ; 

void WriteTinyLog(TINY_LOG *t, char *str)
{
	BUF *b;
	char dt[MAX_PATH];
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	GetDateTimeStrMilli64(dt, sizeof(dt), LocalTime64());
	StrCat(dt, sizeof(dt), ": ");

	b = NewBuf();

	WriteBuf(b, dt, StrLen(dt));
	WriteBuf(b, str, StrLen(str));
	WriteBuf(b, "\r\n", 2);

	Lock(t->Lock);
	{
		FileWrite(t->io, b->Buf, b->Size);
		//FileFlush(t->io);
	}
	Unlock(t->Lock);

	FreeBuf(b);
}