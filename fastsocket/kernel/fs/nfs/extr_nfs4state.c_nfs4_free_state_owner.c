#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_cred; TYPE_1__ so_sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_destroy_wait_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_free_state_owner(struct nfs4_state_owner *sp)
{
	rpc_destroy_wait_queue(&sp->so_sequence.wait);
	put_rpccred(sp->so_cred);
	kfree(sp);
}