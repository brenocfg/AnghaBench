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
typedef  int /*<<< orphan*/  uint64_t ;
struct v9fs_cookie {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void v9fs_cache_inode_get_attr(const void *cookie_netfs_data,
				      uint64_t *size)
{
	const struct v9fs_cookie *vcookie = cookie_netfs_data;
	*size = i_size_read(&vcookie->inode);

	P9_DPRINTK(P9_DEBUG_FSC, "inode %p get attr %llu", &vcookie->inode,
		   *size);
}