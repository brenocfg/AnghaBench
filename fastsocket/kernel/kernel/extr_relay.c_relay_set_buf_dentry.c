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
struct rchan_buf {int /*<<< orphan*/  early_bytes; struct dentry* dentry; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_size; } ;

/* Variables and functions */

__attribute__((used)) static inline void relay_set_buf_dentry(struct rchan_buf *buf,
					struct dentry *dentry)
{
	buf->dentry = dentry;
	buf->dentry->d_inode->i_size = buf->early_bytes;
}