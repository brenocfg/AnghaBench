#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int SubXactEvent ;
typedef  int /*<<< orphan*/  SubTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  CoordinatedRemoteTransactionsSavepointBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoordinatedRemoteTransactionsSavepointRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoordinatedRemoteTransactionsSavepointRollback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InCoordinatedTransaction () ; 
 int /*<<< orphan*/  PopSubXact (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PushSubXact (int /*<<< orphan*/ ) ; 
#define  SUBXACT_EVENT_ABORT_SUB 131 
#define  SUBXACT_EVENT_COMMIT_SUB 130 
#define  SUBXACT_EVENT_PRE_COMMIT_SUB 129 
#define  SUBXACT_EVENT_START_SUB 128 
 int /*<<< orphan*/  UnsetCitusNoticeLevel () ; 

__attribute__((used)) static void
CoordinatedSubTransactionCallback(SubXactEvent event, SubTransactionId subId,
								  SubTransactionId parentSubid, void *arg)
{
	switch (event)
	{
		/*
		 * Our subtransaction stack should be consistent with postgres' internal
		 * transaction stack. In case of subxact begin, postgres calls our
		 * callback after it has pushed the transaction into stack, so we have to
		 * do the same even if worker commands fail, so we PushSubXact() first.
		 * In case of subxact commit, callback is called before pushing subxact to
		 * the postgres transaction stack, so we call PopSubXact() after making sure
		 * worker commands didn't fail. Otherwise, Postgres would roll back that
		 * would cause us to call PopSubXact again.
		 */
		case SUBXACT_EVENT_START_SUB:
		{
			PushSubXact(subId);
			if (InCoordinatedTransaction())
			{
				CoordinatedRemoteTransactionsSavepointBegin(subId);
			}
			break;
		}

		case SUBXACT_EVENT_COMMIT_SUB:
		{
			if (InCoordinatedTransaction())
			{
				CoordinatedRemoteTransactionsSavepointRelease(subId);
			}
			PopSubXact(subId);
			break;
		}

		case SUBXACT_EVENT_ABORT_SUB:
		{
			if (InCoordinatedTransaction())
			{
				CoordinatedRemoteTransactionsSavepointRollback(subId);
			}
			PopSubXact(subId);

			UnsetCitusNoticeLevel();
			break;
		}

		case SUBXACT_EVENT_PRE_COMMIT_SUB:
		{
			/* nothing to do */
			break;
		}
	}
}