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
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 int /*<<< orphan*/  nfsd4_init_recdir (int /*<<< orphan*/ ) ; 
 int nfsd4_recdir_load () ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  user_recovery_dirname ; 

__attribute__((used)) static void
nfsd4_load_reboot_recovery_data(void)
{
	int status;

	nfs4_lock_state();
	nfsd4_init_recdir(user_recovery_dirname);
	status = nfsd4_recdir_load();
	nfs4_unlock_state();
	if (status)
		printk("NFSD: Failure reading reboot recovery data\n");
}