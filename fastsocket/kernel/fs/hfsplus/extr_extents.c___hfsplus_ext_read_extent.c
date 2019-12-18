#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfsplus_extent {int dummy; } ;
struct hfs_find_data {int entrylength; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; TYPE_4__* search_key; TYPE_2__* key; } ;
typedef  int /*<<< orphan*/  hfsplus_extent_rec ;
struct TYPE_7__ {scalar_t__ cnid; scalar_t__ fork_type; } ;
struct TYPE_8__ {TYPE_3__ ext; } ;
struct TYPE_5__ {scalar_t__ cnid; scalar_t__ fork_type; } ;
struct TYPE_6__ {TYPE_1__ ext; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,struct hfsplus_extent*,int /*<<< orphan*/ ,int) ; 
 int hfs_brec_find (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfsplus_ext_build_key (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __hfsplus_ext_read_extent(struct hfs_find_data *fd,
					    struct hfsplus_extent *extent,
					    u32 cnid, u32 block, u8 type)
{
	int res;

	hfsplus_ext_build_key(fd->search_key, cnid, block, type);
	fd->key->ext.cnid = 0;
	res = hfs_brec_find(fd);
	if (res && res != -ENOENT)
		return res;
	if (fd->key->ext.cnid != fd->search_key->ext.cnid ||
	    fd->key->ext.fork_type != fd->search_key->ext.fork_type)
		return -ENOENT;
	if (fd->entrylength != sizeof(hfsplus_extent_rec))
		return -EIO;
	hfs_bnode_read(fd->bnode, extent, fd->entryoffset, sizeof(hfsplus_extent_rec));
	return 0;
}