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
struct nfs_page {int /*<<< orphan*/  wb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_BUSY ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  nfs_wait_bit_uninterruptible ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfs_wait_on_request(struct nfs_page *req)
{
	return wait_on_bit(&req->wb_flags, PG_BUSY,
			nfs_wait_bit_uninterruptible,
			TASK_UNINTERRUPTIBLE);
}