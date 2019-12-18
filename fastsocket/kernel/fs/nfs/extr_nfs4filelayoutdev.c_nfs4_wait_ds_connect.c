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
struct nfs4_pnfs_ds {int /*<<< orphan*/  ds_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4DS_CONNECTING ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  nfs_wait_bit_killable ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_wait_ds_connect(struct nfs4_pnfs_ds *ds)
{
	might_sleep();
	wait_on_bit(&ds->ds_state, NFS4DS_CONNECTING,
			nfs_wait_bit_killable, TASK_KILLABLE);
}