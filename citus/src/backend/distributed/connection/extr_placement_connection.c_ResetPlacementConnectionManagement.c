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

/* Variables and functions */
 int /*<<< orphan*/  ColocatedPlacementsHash ; 
 int /*<<< orphan*/  ConnectionPlacementHash ; 
 int /*<<< orphan*/  ConnectionShardHash ; 
 int /*<<< orphan*/  ResetRelationAccessHash () ; 
 int /*<<< orphan*/  hash_delete_all (int /*<<< orphan*/ ) ; 

void
ResetPlacementConnectionManagement(void)
{
	/* Simply delete all entries */
	hash_delete_all(ConnectionPlacementHash);
	hash_delete_all(ConnectionShardHash);
	hash_delete_all(ColocatedPlacementsHash);
	ResetRelationAccessHash();

	/*
	 * NB: memory for ConnectionReference structs and subordinate data is
	 * deleted by virtue of being allocated in TopTransactionContext.
	 */
}