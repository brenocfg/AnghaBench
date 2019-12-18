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
struct blkio_policy_type {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkio_list ; 
 int /*<<< orphan*/  blkio_list_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void blkio_policy_register(struct blkio_policy_type *blkiop)
{
	spin_lock(&blkio_list_lock);
	list_add_tail(&blkiop->list, &blkio_list);
	spin_unlock(&blkio_list_lock);
}