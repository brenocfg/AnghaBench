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
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_clear_ds_conn_bit(struct nfs4_pnfs_ds *ds)
{
	smp_mb__before_clear_bit();
	clear_bit(NFS4DS_CONNECTING, &ds->ds_state);
	smp_mb__after_clear_bit();
	wake_up_bit(&ds->ds_state, NFS4DS_CONNECTING);
}