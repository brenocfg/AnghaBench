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
struct TYPE_8__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  FlushEvent; int /*<<< orphan*/  RecordQueue; } ;
typedef  int /*<<< orphan*/  RECORD ;
typedef  TYPE_1__ LOG ;
typedef  int /*<<< orphan*/  IO ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ClearBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteRecordToBuffer (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool LogThreadWriteStdout(LOG *log_object, BUF *buffer, IO *io)
{
	RECORD *rec;

	// Retrieve a record from the head of the queue
	LockQueue(log_object->RecordQueue);
	{
		rec = GetNext(log_object->RecordQueue);
	}
	UnlockQueue(log_object->RecordQueue);

	if (rec == NULL)
	{
		Set(log_object->FlushEvent);
		return false;
	}

	ClearBuf(buffer);
	WriteRecordToBuffer(buffer, rec);
	if (!FileWrite(io, buffer->Buf, buffer->Size))
	{
		ClearBuf(buffer);
	}
	Free(rec);

	return true;
}