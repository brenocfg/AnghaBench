#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {int /*<<< orphan*/  fe_msgbuf; scalar_t__ binary; } ;
struct TYPE_5__ {TYPE_3__ fileCompat; scalar_t__ writeLocalFile; TYPE_2__* copyOutState; int /*<<< orphan*/ * connectionList; } ;
typedef  TYPE_1__ RemoteFileDestReceiver ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_2__* CopyOutState ;

/* Variables and functions */
 int /*<<< orphan*/  AppendCopyBinaryFooters (TYPE_2__*) ; 
 int /*<<< orphan*/  BroadcastCopyData (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndRemoteCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteToLocalFile (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RemoteFileDestReceiverShutdown(DestReceiver *destReceiver)
{
	RemoteFileDestReceiver *resultDest = (RemoteFileDestReceiver *) destReceiver;

	List *connectionList = resultDest->connectionList;
	CopyOutState copyOutState = resultDest->copyOutState;

	if (copyOutState->binary)
	{
		/* send footers when using binary encoding */
		resetStringInfo(copyOutState->fe_msgbuf);
		AppendCopyBinaryFooters(copyOutState);
		BroadcastCopyData(copyOutState->fe_msgbuf, connectionList);

		if (resultDest->writeLocalFile)
		{
			WriteToLocalFile(copyOutState->fe_msgbuf, &resultDest->fileCompat);
		}
	}

	/* close the COPY input */
	EndRemoteCopy(0, connectionList);

	if (resultDest->writeLocalFile)
	{
		FileClose(resultDest->fileCompat.fd);
	}
}