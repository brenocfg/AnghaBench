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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int) ; 
 scalar_t__ INVALID_SHARD_ID ; 
 int /*<<< orphan*/  LockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  SET_LOCKTAG_SHARD_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
LockShardResource(uint64 shardId, LOCKMODE lockmode)
{
	LOCKTAG tag;
	const bool sessionLock = false;
	const bool dontWait = false;

	AssertArg(shardId != INVALID_SHARD_ID);

	SET_LOCKTAG_SHARD_RESOURCE(tag, MyDatabaseId, shardId);

	(void) LockAcquire(&tag, lockmode, sessionLock, dontWait);
}