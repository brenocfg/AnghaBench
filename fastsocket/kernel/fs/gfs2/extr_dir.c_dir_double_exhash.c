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
typedef  int u32 ;
struct gfs2_inode {int i_depth; void** i_hash_cache; int /*<<< orphan*/  i_inode; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  void* __be64 ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_NOFS ; 
 scalar_t__ IS_ERR (void**) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PTR_ERR (void**) ; 
 int __GFP_NOWARN ; 
 void** __vmalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 void** gfs2_dir_get_hash_table (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dir_hash_inval (struct gfs2_inode*) ; 
 int gfs2_dir_write_data (struct gfs2_inode*,char*,int /*<<< orphan*/ ,int) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  i_size_write (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_vmalloc_addr (void**) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void** kmalloc (int,int) ; 
 int /*<<< orphan*/  vfree (void**) ; 

__attribute__((used)) static int dir_double_exhash(struct gfs2_inode *dip)
{
	struct buffer_head *dibh;
	u32 hsize;
	u32 hsize_bytes;
	__be64 *hc;
	__be64 *hc2, *h;
	int x;
	int error = 0;

	hsize = 1 << dip->i_depth;
	hsize_bytes = hsize * sizeof(__be64);

	hc = gfs2_dir_get_hash_table(dip);
	if (IS_ERR(hc))
		return PTR_ERR(hc);

	hc2 = kmalloc(hsize_bytes * 2, GFP_NOFS | __GFP_NOWARN);
	if (hc2 == NULL)
		hc2 = __vmalloc(hsize_bytes * 2, GFP_NOFS, PAGE_KERNEL);

	if (!hc2)
		return -ENOMEM;

	h = hc2;
	error = gfs2_meta_inode_buffer(dip, &dibh);
	if (error)
		goto out_kfree;

	for (x = 0; x < hsize; x++) {
		*h++ = *hc;
		*h++ = *hc;
		hc++;
	}

	error = gfs2_dir_write_data(dip, (char *)hc2, 0, hsize_bytes * 2);
	if (error != (hsize_bytes * 2))
		goto fail;

	gfs2_dir_hash_inval(dip);
	dip->i_hash_cache = hc2;
	dip->i_depth++;
	gfs2_dinode_out(dip, dibh->b_data);
	brelse(dibh);
	return 0;

fail:
	/* Replace original hash table & size */
	gfs2_dir_write_data(dip, (char *)hc, 0, hsize_bytes);
	i_size_write(&dip->i_inode, hsize_bytes);
	gfs2_dinode_out(dip, dibh->b_data);
	brelse(dibh);
out_kfree:
	if (is_vmalloc_addr(hc2))
		vfree(hc2);
	else
		kfree(hc2);
	return error;
}