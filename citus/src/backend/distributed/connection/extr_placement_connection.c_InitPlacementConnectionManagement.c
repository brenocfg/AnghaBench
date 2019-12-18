#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {int keysize; int entrysize; void* hcxt; void* hash; int /*<<< orphan*/  match; } ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  ConnectionShardHashKey ;
typedef  int /*<<< orphan*/  ConnectionShardHashEntry ;
typedef  int /*<<< orphan*/  ConnectionPlacementHashKey ;
typedef  int /*<<< orphan*/  ConnectionPlacementHashEntry ;
typedef  int /*<<< orphan*/  ColocatedPlacementsHashKey ;
typedef  int /*<<< orphan*/  ColocatedPlacementsHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateRelationAccessHash () ; 
 void* ColocatedPlacementsHash ; 
 int /*<<< orphan*/  ColocatedPlacementsHashCompare ; 
 void* ColocatedPlacementsHashHash ; 
 void* ConnectionContext ; 
 void* ConnectionPlacementHash ; 
 void* ConnectionShardHash ; 
 int HASH_BLOBS ; 
 int HASH_COMPARE ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int HASH_FUNCTION ; 
 void* hash_create (char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* tag_hash ; 

void
InitPlacementConnectionManagement(void)
{
	HASHCTL info;
	uint32 hashFlags = 0;

	/* create (placementId) -> [ConnectionReference] hash */
	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(ConnectionPlacementHashKey);
	info.entrysize = sizeof(ConnectionPlacementHashEntry);
	info.hash = tag_hash;
	info.hcxt = ConnectionContext;
	hashFlags = (HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);

	ConnectionPlacementHash = hash_create("citus connection cache (placementid)",
										  64, &info, hashFlags);

	/* create (colocated placement identity) -> [ConnectionReference] hash */
	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(ColocatedPlacementsHashKey);
	info.entrysize = sizeof(ColocatedPlacementsHashEntry);
	info.hash = ColocatedPlacementsHashHash;
	info.match = ColocatedPlacementsHashCompare;
	info.hcxt = ConnectionContext;
	hashFlags = (HASH_ELEM | HASH_FUNCTION | HASH_CONTEXT | HASH_COMPARE);

	ColocatedPlacementsHash = hash_create("citus connection cache (colocated placements)",
										  64, &info, hashFlags);

	/* create (shardId) -> [ConnectionShardHashEntry] hash */
	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(ConnectionShardHashKey);
	info.entrysize = sizeof(ConnectionShardHashEntry);
	info.hash = tag_hash;
	info.hcxt = ConnectionContext;
	hashFlags = (HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);

	ConnectionShardHash = hash_create("citus connection cache (shardid)",
									  64, &info, hashFlags);

	/* (relationId) = [relationAccessMode] hash */
	AllocateRelationAccessHash();
}