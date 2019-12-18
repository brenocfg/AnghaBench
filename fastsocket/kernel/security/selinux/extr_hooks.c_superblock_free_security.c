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
struct superblock_security_struct {int /*<<< orphan*/  list; } ;
struct super_block {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct superblock_security_struct*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_security_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void superblock_free_security(struct super_block *sb)
{
	struct superblock_security_struct *sbsec = sb->s_security;

	spin_lock(&sb_security_lock);
	if (!list_empty(&sbsec->list))
		list_del_init(&sbsec->list);
	spin_unlock(&sb_security_lock);

	sb->s_security = NULL;
	kfree(sbsec);
}