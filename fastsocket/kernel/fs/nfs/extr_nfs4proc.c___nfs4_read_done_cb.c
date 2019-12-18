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
struct nfs_read_data {TYPE_1__* header; } ;
struct TYPE_2__ {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_invalidate_atime (int /*<<< orphan*/ ) ; 

void __nfs4_read_done_cb(struct nfs_read_data *data)
{
	nfs_invalidate_atime(data->header->inode);
}