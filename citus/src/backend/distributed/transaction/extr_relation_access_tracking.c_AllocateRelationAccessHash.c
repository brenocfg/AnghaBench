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
struct TYPE_4__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  RelationAccessHashKey ;
typedef  int /*<<< orphan*/  RelationAccessHashEntry ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionContext ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  RelationAccessHash ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tag_hash ; 

void
AllocateRelationAccessHash(void)
{
	HASHCTL info;
	uint32 hashFlags = 0;

	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(RelationAccessHashKey);
	info.entrysize = sizeof(RelationAccessHashEntry);
	info.hash = tag_hash;
	info.hcxt = ConnectionContext;
	hashFlags = (HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);

	RelationAccessHash = hash_create("citus connection cache (relationid)",
									 8, &info, hashFlags);
}