#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct jffs2_inode_info {TYPE_1__* inocache; } ;
struct dentry {TYPE_2__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  ino; int /*<<< orphan*/  pino_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  JFFS2_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jffs2_inode_info* JFFS2_INODE_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *jffs2_get_parent(struct dentry *child)
{
	struct jffs2_inode_info *f;
	uint32_t pino;

	BUG_ON(!S_ISDIR(child->d_inode->i_mode));

	f = JFFS2_INODE_INFO(child->d_inode);

	pino = f->inocache->pino_nlink;

	JFFS2_DEBUG("Parent of directory ino #%u is #%u\n",
		    f->inocache->ino, pino);

	return d_obtain_alias(jffs2_iget(child->d_inode->i_sb, pino));
}