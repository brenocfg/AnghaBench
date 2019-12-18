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
typedef  scalar_t__ int64 ;
struct TYPE_3__ {scalar_t__ anchorShardId; scalar_t__ replicationModel; int /*<<< orphan*/  taskPlacementList; } ;
typedef  TYPE_1__ Task ;
typedef  int /*<<< orphan*/  ShardInterval ;
typedef  scalar_t__ RowModifyLevel ;
typedef  scalar_t__ LOCKMODE ;

/* Variables and functions */
 scalar_t__ AllModificationsCommutative ; 
 scalar_t__ ExclusiveLock ; 
 scalar_t__ INVALID_SHARD_ID ; 
 int /*<<< orphan*/ * LoadShardInterval (scalar_t__) ; 
 scalar_t__ NoLock ; 
 scalar_t__ REPLICATION_MODEL_2PC ; 
 scalar_t__ ROW_MODIFY_NONCOMMUTATIVE ; 
 scalar_t__ ROW_MODIFY_READONLY ; 
 scalar_t__ RowExclusiveLock ; 
 int /*<<< orphan*/  SerializeNonCommutativeWrites (int /*<<< orphan*/ ,scalar_t__) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
AcquireExecutorShardLockForRowModify(Task *task, RowModifyLevel modLevel)
{
	LOCKMODE lockMode = NoLock;
	int64 shardId = task->anchorShardId;

	if (shardId == INVALID_SHARD_ID)
	{
		return;
	}

	if (modLevel <= ROW_MODIFY_READONLY)
	{
		/*
		 * The executor shard lock is used to maintain consistency between
		 * replicas and therefore no lock is required for read-only queries
		 * or in general when there is only one replica.
		 */

		lockMode = NoLock;
	}
	else if (list_length(task->taskPlacementList) == 1)
	{
		if (task->replicationModel == REPLICATION_MODEL_2PC)
		{
			/*
			 * While we don't need a lock to ensure writes are applied in
			 * a consistent order when there is a single replica. We also use
			 * shard resource locks as a crude implementation of SELECT..
			 * FOR UPDATE on reference tables, so we should always take
			 * a lock that conflicts with the FOR UPDATE/SHARE locks.
			 */
			lockMode = RowExclusiveLock;
		}
		else
		{
			/*
			 * When there is no replication, the worker itself can decide on
			 * on the order in which writes are applied.
			 */
			lockMode = NoLock;
		}
	}
	else if (AllModificationsCommutative)
	{
		/*
		 * Bypass commutativity checks when citus.all_modifications_commutative
		 * is enabled.
		 *
		 * A RowExclusiveLock does not conflict with itself and therefore allows
		 * multiple commutative commands to proceed concurrently. It does
		 * conflict with ExclusiveLock, which may still be obtained by another
		 * session that executes an UPDATE/DELETE/UPSERT command with
		 * citus.all_modifications_commutative disabled.
		 */

		lockMode = RowExclusiveLock;
	}
	else if (modLevel < ROW_MODIFY_NONCOMMUTATIVE)
	{
		/*
		 * An INSERT commutes with other INSERT commands, since performing them
		 * out-of-order only affects the table order on disk, but not the
		 * contents.
		 *
		 * When a unique constraint exists, INSERTs are not strictly commutative,
		 * but whichever INSERT comes last will error out and thus has no effect.
		 * INSERT is not commutative with UPDATE/DELETE/UPSERT, since the
		 * UPDATE/DELETE/UPSERT may consider the INSERT, depending on execution
		 * order.
		 *
		 * A RowExclusiveLock does not conflict with itself and therefore allows
		 * multiple INSERT commands to proceed concurrently. It conflicts with
		 * ExclusiveLock obtained by UPDATE/DELETE/UPSERT, ensuring those do
		 * not run concurrently with INSERT.
		 */

		lockMode = RowExclusiveLock;
	}
	else
	{
		/*
		 * UPDATE/DELETE/UPSERT commands do not commute with other modifications
		 * since the rows modified by one command may be affected by the outcome
		 * of another command.
		 *
		 * We need to handle upsert before INSERT, because PostgreSQL models
		 * upsert commands as INSERT with an ON CONFLICT section.
		 *
		 * ExclusiveLock conflicts with all lock types used by modifications
		 * and therefore prevents other modifications from running
		 * concurrently.
		 */

		lockMode = ExclusiveLock;
	}

	if (lockMode != NoLock)
	{
		ShardInterval *shardInterval = LoadShardInterval(shardId);

		SerializeNonCommutativeWrites(list_make1(shardInterval), lockMode);
	}
}