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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  SET_LOCKTAG_SHARD_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
UnlockShardResource(uint64 shardId, LOCKMODE lockmode)
{
	LOCKTAG tag;
	const bool sessionLock = false;

	SET_LOCKTAG_SHARD_RESOURCE(tag, MyDatabaseId, shardId);

	LockRelease(&tag, lockmode, sessionLock);
}