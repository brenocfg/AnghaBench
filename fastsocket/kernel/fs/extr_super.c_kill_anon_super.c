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
struct super_block {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_shutdown_super (struct super_block*) ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unnamed_dev_ida ; 
 int /*<<< orphan*/  unnamed_dev_lock ; 
 int unnamed_dev_start ; 

void kill_anon_super(struct super_block *sb)
{
	int slot = MINOR(sb->s_dev);

	generic_shutdown_super(sb);
	spin_lock(&unnamed_dev_lock);
	ida_remove(&unnamed_dev_ida, slot);
	if (slot < unnamed_dev_start)
		unnamed_dev_start = slot;
	spin_unlock(&unnamed_dev_lock);
}