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
struct ocfs2_disk_dqtrailer {int dummy; } ;

/* Variables and functions */
 int OCFS2_QBLK_RESERVED_SPACE ; 

__attribute__((used)) static inline struct ocfs2_disk_dqtrailer *ocfs2_block_dqtrailer(int blocksize,
								 void *buf)
{
	char *ptr = buf;
	ptr += blocksize - OCFS2_QBLK_RESERVED_SPACE;

	return (struct ocfs2_disk_dqtrailer *)ptr;
}