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
struct hfs_find_data {int entrylength; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int hfs_brec_find (struct hfs_find_data*) ; 

int hfs_brec_read(struct hfs_find_data *fd, void *rec, int rec_len)
{
	int res;

	res = hfs_brec_find(fd);
	if (res)
		return res;
	if (fd->entrylength > rec_len)
		return -EINVAL;
	hfs_bnode_read(fd->bnode, rec, fd->entryoffset, fd->entrylength);
	return 0;
}