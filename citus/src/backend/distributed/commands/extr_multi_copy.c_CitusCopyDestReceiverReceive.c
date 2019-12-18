#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int /*<<< orphan*/  connectionStateHash; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_1__ CitusCopyDestReceiver ;

/* Variables and functions */
 int CitusSendTupleToPlacements (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * ConnectionStateList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  UnclaimCopyConnections (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
CitusCopyDestReceiverReceive(TupleTableSlot *slot, DestReceiver *dest)
{
	bool result = false;
	CitusCopyDestReceiver *copyDest = (CitusCopyDestReceiver *) dest;

	PG_TRY();
	{
		result = CitusSendTupleToPlacements(slot, copyDest);
	}
	PG_CATCH();
	{
		/*
		 * We might be able to recover from errors with ROLLBACK TO SAVEPOINT,
		 * so unclaim the connections before throwing errors.
		 */
		List *connectionStateList = ConnectionStateList(copyDest->connectionStateHash);
		UnclaimCopyConnections(connectionStateList);

		PG_RE_THROW();
	}
	PG_END_TRY();

	return result;
}