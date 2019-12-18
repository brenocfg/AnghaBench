#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {scalar_t__ hash_version; int unused_flags; unsigned int indirect_levels; int info_length; } ;
struct dx_root {TYPE_1__ info; } ;
struct dx_node {struct dx_entry* entries; } ;
struct dx_hash_info {scalar_t__ hash_version; scalar_t__ hash; int /*<<< orphan*/  seed; } ;
struct dx_frame {struct buffer_head* bh; struct dx_entry* at; struct dx_entry* entries; } ;
struct dx_entry {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_4__ {scalar_t__ s_hash_unsigned; int /*<<< orphan*/  s_hash_seed; } ;

/* Variables and functions */
 scalar_t__ DX_HASH_HALF_MD4 ; 
 scalar_t__ DX_HASH_LEGACY ; 
 scalar_t__ DX_HASH_TEA ; 
 int ERR_BAD_DX_DIR ; 
 TYPE_2__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dx_get_block (struct dx_entry*) ; 
 unsigned int dx_get_count (struct dx_entry*) ; 
 scalar_t__ dx_get_hash (struct dx_entry*) ; 
 unsigned int dx_get_limit (struct dx_entry*) ; 
 unsigned int dx_node_limit (struct inode*) ; 
 unsigned int dx_root_limit (struct inode*,int) ; 
 int /*<<< orphan*/  dxtrace (int /*<<< orphan*/ ) ; 
 struct buffer_head* ext4_bread (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext4_warning (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ext4fs_dirhash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dx_hash_info*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static struct dx_frame *
dx_probe(const struct qstr *d_name, struct inode *dir,
	 struct dx_hash_info *hinfo, struct dx_frame *frame_in, int *err)
{
	unsigned count, indirect;
	struct dx_entry *at, *entries, *p, *q, *m;
	struct dx_root *root;
	struct buffer_head *bh;
	struct dx_frame *frame = frame_in;
	u32 hash;

	frame->bh = NULL;
	if (!(bh = ext4_bread (NULL,dir, 0, 0, err)))
		goto fail;
	root = (struct dx_root *) bh->b_data;
	if (root->info.hash_version != DX_HASH_TEA &&
	    root->info.hash_version != DX_HASH_HALF_MD4 &&
	    root->info.hash_version != DX_HASH_LEGACY) {
		ext4_warning(dir->i_sb, "Unrecognised inode hash code %d",
			     root->info.hash_version);
		brelse(bh);
		*err = ERR_BAD_DX_DIR;
		goto fail;
	}
	hinfo->hash_version = root->info.hash_version;
	if (hinfo->hash_version <= DX_HASH_TEA)
		hinfo->hash_version += EXT4_SB(dir->i_sb)->s_hash_unsigned;
	hinfo->seed = EXT4_SB(dir->i_sb)->s_hash_seed;
	if (d_name)
		ext4fs_dirhash(d_name->name, d_name->len, hinfo);
	hash = hinfo->hash;

	if (root->info.unused_flags & 1) {
		ext4_warning(dir->i_sb, "Unimplemented inode hash flags: %#06x",
			     root->info.unused_flags);
		brelse(bh);
		*err = ERR_BAD_DX_DIR;
		goto fail;
	}

	if ((indirect = root->info.indirect_levels) > 1) {
		ext4_warning(dir->i_sb, "Unimplemented inode hash depth: %#06x",
			     root->info.indirect_levels);
		brelse(bh);
		*err = ERR_BAD_DX_DIR;
		goto fail;
	}

	entries = (struct dx_entry *) (((char *)&root->info) +
				       root->info.info_length);

	if (dx_get_limit(entries) != dx_root_limit(dir,
						   root->info.info_length)) {
		ext4_warning(dir->i_sb, "dx entry: limit != root limit");
		brelse(bh);
		*err = ERR_BAD_DX_DIR;
		goto fail;
	}

	dxtrace(printk("Look up %x", hash));
	while (1)
	{
		count = dx_get_count(entries);
		if (!count || count > dx_get_limit(entries)) {
			ext4_warning(dir->i_sb,
				     "dx entry: no count or count > limit");
			brelse(bh);
			*err = ERR_BAD_DX_DIR;
			goto fail2;
		}

		p = entries + 1;
		q = entries + count - 1;
		while (p <= q)
		{
			m = p + (q - p)/2;
			dxtrace(printk("."));
			if (dx_get_hash(m) > hash)
				q = m - 1;
			else
				p = m + 1;
		}

		if (0) // linear search cross check
		{
			unsigned n = count - 1;
			at = entries;
			while (n--)
			{
				dxtrace(printk(","));
				if (dx_get_hash(++at) > hash)
				{
					at--;
					break;
				}
			}
			assert (at == p - 1);
		}

		at = p - 1;
		dxtrace(printk(" %x->%u\n", at == entries? 0: dx_get_hash(at), dx_get_block(at)));
		frame->bh = bh;
		frame->entries = entries;
		frame->at = at;
		if (!indirect--) return frame;
		if (!(bh = ext4_bread (NULL,dir, dx_get_block(at), 0, err)))
			goto fail2;
		at = entries = ((struct dx_node *) bh->b_data)->entries;
		if (dx_get_limit(entries) != dx_node_limit (dir)) {
			ext4_warning(dir->i_sb,
				     "dx entry: limit != node limit");
			brelse(bh);
			*err = ERR_BAD_DX_DIR;
			goto fail2;
		}
		frame++;
		frame->bh = NULL;
	}
fail2:
	while (frame >= frame_in) {
		brelse(frame->bh);
		frame--;
	}
fail:
	if (*err == ERR_BAD_DX_DIR)
		ext4_warning(dir->i_sb,
			     "Corrupt dir inode %ld, running e2fsck is "
			     "recommended.", dir->i_ino);
	return NULL;
}