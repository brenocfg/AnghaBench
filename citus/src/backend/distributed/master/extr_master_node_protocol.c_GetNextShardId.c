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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CitusExtensionOwner () ; 
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserIdAndSecContext (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ NextShardId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResolveRelationId (int /*<<< orphan*/ *,int) ; 
 int SECURITY_LOCAL_USERID_CHANGE ; 
 int /*<<< orphan*/  SHARDID_SEQUENCE_NAME ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cstring_to_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nextval_oid ; 

uint64
GetNextShardId()
{
	text *sequenceName = NULL;
	Oid sequenceId = InvalidOid;
	Datum sequenceIdDatum = 0;
	Oid savedUserId = InvalidOid;
	int savedSecurityContext = 0;
	Datum shardIdDatum = 0;
	uint64 shardId = 0;

	/*
	 * In regression tests, we would like to generate shard IDs consistently
	 * even if the tests run in parallel. Instead of the sequence, we can use
	 * the next_shard_id GUC to specify which shard ID the current session should
	 * generate next. The GUC is automatically increased by 1 every time a new
	 * shard ID is generated.
	 */
	if (NextShardId > 0)
	{
		shardId = NextShardId;
		NextShardId += 1;

		return shardId;
	}

	sequenceName = cstring_to_text(SHARDID_SEQUENCE_NAME);
	sequenceId = ResolveRelationId(sequenceName, false);
	sequenceIdDatum = ObjectIdGetDatum(sequenceId);

	GetUserIdAndSecContext(&savedUserId, &savedSecurityContext);
	SetUserIdAndSecContext(CitusExtensionOwner(), SECURITY_LOCAL_USERID_CHANGE);

	/* generate new and unique shardId from sequence */
	shardIdDatum = DirectFunctionCall1(nextval_oid, sequenceIdDatum);

	SetUserIdAndSecContext(savedUserId, savedSecurityContext);

	shardId = DatumGetInt64(shardIdDatum);

	return shardId;
}