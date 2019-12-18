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
struct the_nilfs {int dummy; } ;
struct nilfs_argv {size_t v_nmembs; } ;

/* Variables and functions */
 int nilfs_dat_freev (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  nilfs_dat_inode (struct the_nilfs*) ; 

__attribute__((used)) static int nilfs_ioctl_free_vblocknrs(struct the_nilfs *nilfs,
				      struct nilfs_argv *argv, void *buf)
{
	size_t nmembs = argv->v_nmembs;
	int ret;

	ret = nilfs_dat_freev(nilfs_dat_inode(nilfs), buf, nmembs);

	return (ret < 0) ? ret : nmembs;
}