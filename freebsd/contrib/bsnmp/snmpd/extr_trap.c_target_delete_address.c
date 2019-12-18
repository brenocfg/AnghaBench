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
struct target_address {scalar_t__ status; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 scalar_t__ RowStatus_active ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct target_address*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct target_address*) ; 
 int /*<<< orphan*/  ta ; 
 int /*<<< orphan*/  target_address ; 
 int /*<<< orphan*/  target_addresslist ; 

int
target_delete_address(struct target_address *addrs)
{
	SLIST_REMOVE(&target_addresslist, addrs, target_address, ta);
	if (addrs->status == RowStatus_active)
		close(addrs->socket);
	free(addrs);

	return (0);
}