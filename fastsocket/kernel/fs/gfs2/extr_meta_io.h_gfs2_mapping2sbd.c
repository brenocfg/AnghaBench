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
struct inode {TYPE_1__* i_sb; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_glock {struct gfs2_sbd* gl_sbd; } ;
struct address_space {int /*<<< orphan*/ * a_ops; struct inode* host; } ;
struct TYPE_2__ {struct gfs2_sbd* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_meta_aops ; 

__attribute__((used)) static inline struct gfs2_sbd *gfs2_mapping2sbd(struct address_space *mapping)
{
	struct inode *inode = mapping->host;
	if (mapping->a_ops == &gfs2_meta_aops)
		return (((struct gfs2_glock *)mapping) - 1)->gl_sbd;
	else
		return inode->i_sb->s_fs_info;
}