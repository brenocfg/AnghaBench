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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct gfs2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gfs2_dir_get_hash_table (struct gfs2_inode*) ; 

__attribute__((used)) static int get_leaf_nr(struct gfs2_inode *dip, u32 index,
		       u64 *leaf_out)
{
	__be64 *hash;

	hash = gfs2_dir_get_hash_table(dip);
	if (IS_ERR(hash))
		return PTR_ERR(hash);
	*leaf_out = be64_to_cpu(*(hash + index));
	return 0;
}