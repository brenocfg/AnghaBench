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
struct pohmelfs_sb {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int pohmelfs_copy_config (struct pohmelfs_sb*) ; 
 int /*<<< orphan*/  pohmelfs_state_exit (struct pohmelfs_sb*) ; 

int pohmelfs_state_init(struct pohmelfs_sb *psb)
{
	int err = -ENOMEM;

	err = pohmelfs_copy_config(psb);
	if (err) {
		pohmelfs_state_exit(psb);
		return err;
	}

	return 0;
}