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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ConnectionPlacementHash ; 
 scalar_t__ hash_get_num_entries (int /*<<< orphan*/ *) ; 

bool
AnyConnectionAccessedPlacements(void)
{
	/* this is initialized on PG_INIT */
	Assert(ConnectionPlacementHash != NULL);

	return hash_get_num_entries(ConnectionPlacementHash) > 0;
}