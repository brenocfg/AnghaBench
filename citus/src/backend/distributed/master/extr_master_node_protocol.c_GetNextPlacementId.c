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
 scalar_t__ NextPlacementId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLACEMENTID_SEQUENCE_NAME ; 
 int /*<<< orphan*/  ResolveRelationId (int /*<<< orphan*/ *,int) ; 
 int SECURITY_LOCAL_USERID_CHANGE ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cstring_to_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nextval_oid ; 

uint64
GetNextPlacementId(void)
{
	text *sequenceName = NULL;
	Oid sequenceId = InvalidOid;
	Datum sequenceIdDatum = 0;
	Oid savedUserId = InvalidOid;
	int savedSecurityContext = 0;
	Datum placementIdDatum = 0;
	uint64 placementId = 0;

	/*
	 * In regression tests, we would like to generate placement IDs consistently
	 * even if the tests run in parallel. Instead of the sequence, we can use
	 * the next_placement_id GUC to specify which shard ID the current session
	 * should generate next. The GUC is automatically increased by 1 every time
	 * a new placement ID is generated.
	 */
	if (NextPlacementId > 0)
	{
		placementId = NextPlacementId;
		NextPlacementId += 1;

		return placementId;
	}

	sequenceName = cstring_to_text(PLACEMENTID_SEQUENCE_NAME);
	sequenceId = ResolveRelationId(sequenceName, false);
	sequenceIdDatum = ObjectIdGetDatum(sequenceId);

	GetUserIdAndSecContext(&savedUserId, &savedSecurityContext);
	SetUserIdAndSecContext(CitusExtensionOwner(), SECURITY_LOCAL_USERID_CHANGE);

	/* generate new and unique placement id from sequence */
	placementIdDatum = DirectFunctionCall1(nextval_oid, sequenceIdDatum);

	SetUserIdAndSecContext(savedUserId, savedSecurityContext);

	placementId = DatumGetInt64(placementIdDatum);

	return placementId;
}