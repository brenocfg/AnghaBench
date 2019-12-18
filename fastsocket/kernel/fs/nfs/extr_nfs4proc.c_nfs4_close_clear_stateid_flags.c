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
struct nfs4_state {TYPE_1__* owner; int /*<<< orphan*/  flags; } ;
typedef  int fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  so_lock; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  NFS_O_RDONLY_STATE ; 
 int /*<<< orphan*/  NFS_O_RDWR_STATE ; 
 int /*<<< orphan*/  NFS_O_WRONLY_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_close_clear_stateid_flags(struct nfs4_state *state,
		fmode_t fmode)
{
	spin_lock(&state->owner->so_lock);
	if (!(fmode & FMODE_READ))
		clear_bit(NFS_O_RDONLY_STATE, &state->flags);
	if (!(fmode & FMODE_WRITE))
		clear_bit(NFS_O_WRONLY_STATE, &state->flags);
	clear_bit(NFS_O_RDWR_STATE, &state->flags);
	spin_unlock(&state->owner->so_lock);
}