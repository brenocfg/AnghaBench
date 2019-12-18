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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {struct ext4_extent* p_ext; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  double_down_write_data_sem (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  double_up_write_data_sem (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_invalidate_cache (struct inode*) ; 
 int ext_depth (struct inode*) ; 
 int get_ext_path (struct inode*,scalar_t__,struct ext4_ext_path**) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mext_calc_swap_extents (struct ext4_extent*,struct ext4_extent*,scalar_t__,scalar_t__,scalar_t__) ; 
 int mext_leaf_block (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,struct ext4_extent*,scalar_t__*) ; 

__attribute__((used)) static int
mext_replace_branches(handle_t *handle, struct inode *orig_inode,
			   struct inode *donor_inode, ext4_lblk_t from,
			   ext4_lblk_t count, int *err)
{
	struct ext4_ext_path *orig_path = NULL;
	struct ext4_ext_path *donor_path = NULL;
	struct ext4_extent *oext, *dext;
	struct ext4_extent tmp_dext, tmp_oext;
	ext4_lblk_t orig_off = from, donor_off = from;
	int depth;
	int replaced_count = 0;
	int dext_alen;

	/* Protect extent trees against block allocations via delalloc */
	double_down_write_data_sem(orig_inode, donor_inode);

	/* Get the original extent for the block "orig_off" */
	*err = get_ext_path(orig_inode, orig_off, &orig_path);
	if (*err)
		goto out;

	/* Get the donor extent for the head */
	*err = get_ext_path(donor_inode, donor_off, &donor_path);
	if (*err)
		goto out;
	depth = ext_depth(orig_inode);
	oext = orig_path[depth].p_ext;
	tmp_oext = *oext;

	depth = ext_depth(donor_inode);
	dext = donor_path[depth].p_ext;
	tmp_dext = *dext;

	*err = mext_calc_swap_extents(&tmp_dext, &tmp_oext, orig_off,
				      donor_off, count);
	if (*err)
		goto out;

	/* Loop for the donor extents */
	while (1) {
		/* The extent for donor must be found. */
		if (!dext) {
			ext4_error(donor_inode->i_sb,
				   "The extent for donor must be found");
			*err = -EIO;
			goto out;
		} else if (donor_off != le32_to_cpu(tmp_dext.ee_block)) {
			ext4_error(donor_inode->i_sb,
				"Donor offset(%u) and the first block of donor "
				"extent(%u) should be equal",
				donor_off,
				le32_to_cpu(tmp_dext.ee_block));
			*err = -EIO;
			goto out;
		}

		/* Set donor extent to orig extent */
		*err = mext_leaf_block(handle, orig_inode,
					   orig_path, &tmp_dext, &orig_off);
		if (*err)
			goto out;

		/* Set orig extent to donor extent */
		*err = mext_leaf_block(handle, donor_inode,
					   donor_path, &tmp_oext, &donor_off);
		if (*err)
			goto out;

		dext_alen = ext4_ext_get_actual_len(&tmp_dext);
		replaced_count += dext_alen;
		donor_off += dext_alen;
		orig_off += dext_alen;

		/* Already moved the expected blocks */
		if (replaced_count >= count)
			break;

		if (orig_path)
			ext4_ext_drop_refs(orig_path);
		*err = get_ext_path(orig_inode, orig_off, &orig_path);
		if (*err)
			goto out;
		depth = ext_depth(orig_inode);
		oext = orig_path[depth].p_ext;
		tmp_oext = *oext;

		if (donor_path)
			ext4_ext_drop_refs(donor_path);
		*err = get_ext_path(donor_inode, donor_off, &donor_path);
		if (*err)
			goto out;
		depth = ext_depth(donor_inode);
		dext = donor_path[depth].p_ext;
		tmp_dext = *dext;

		*err = mext_calc_swap_extents(&tmp_dext, &tmp_oext, orig_off,
					   donor_off, count - replaced_count);
		if (*err)
			goto out;
	}

out:
	if (orig_path) {
		ext4_ext_drop_refs(orig_path);
		kfree(orig_path);
	}
	if (donor_path) {
		ext4_ext_drop_refs(donor_path);
		kfree(donor_path);
	}

	ext4_ext_invalidate_cache(orig_inode);
	ext4_ext_invalidate_cache(donor_inode);

	double_up_write_data_sem(orig_inode, donor_inode);

	return replaced_count;
}