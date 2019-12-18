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
typedef  int /*<<< orphan*/  filename ;
struct TYPE_7__ {int Size; } ;
struct TYPE_6__ {int wYear; int wMonth; int wDay; int wHour; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DumpBuf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  LocalTime (TYPE_1__*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MakeDirEx (char*) ; 
 TYPE_2__* probe_buf ; 
 int /*<<< orphan*/  probe_lock ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FreeProbe()
{
	if (probe_buf->Size >= 1)
	{
		SYSTEMTIME st;
		char filename[MAX_SIZE];

		// Write all to the file
		MakeDirEx("@probe_log");

		LocalTime(&st);

		snprintf(filename, sizeof(filename), "@probe_log/%04u%02u%02u_%02u%02u%02u.log",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		DumpBuf(probe_buf, filename);
	}

	FreeBuf(probe_buf);
	DeleteLock(probe_lock);
}