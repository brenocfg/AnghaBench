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
struct MultiConnection {int /*<<< orphan*/  referencedPlacements; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 

void
ResetShardPlacementAssociation(struct MultiConnection *connection)
{
	dlist_init(&connection->referencedPlacements);
}