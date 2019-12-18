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
struct super_block {int dummy; } ;
struct adfs_sb_info {int s_map_size; unsigned int s_ids_per_zone; int /*<<< orphan*/  s_map2blk; } ;

/* Variables and functions */
 unsigned int ADFS_ROOT_FRAG ; 
 struct adfs_sb_info* ADFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  adfs_error (struct super_block*,char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  adfs_map_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int scan_map (struct adfs_sb_info*,unsigned int,unsigned int,unsigned int) ; 
 unsigned int signed_asl (int,int /*<<< orphan*/ ) ; 

int
adfs_map_lookup(struct super_block *sb, unsigned int frag_id,
		unsigned int offset)
{
	struct adfs_sb_info *asb = ADFS_SB(sb);
	unsigned int zone, mapoff;
	int result;

	/*
	 * map & root fragment is special - it starts in the center of the
	 * disk.  The other fragments start at zone (frag / ids_per_zone)
	 */
	if (frag_id == ADFS_ROOT_FRAG)
		zone = asb->s_map_size >> 1;
	else
		zone = frag_id / asb->s_ids_per_zone;

	if (zone >= asb->s_map_size)
		goto bad_fragment;

	/* Convert sector offset to map offset */
	mapoff = signed_asl(offset, -asb->s_map2blk);

	read_lock(&adfs_map_lock);
	result = scan_map(asb, zone, frag_id, mapoff);
	read_unlock(&adfs_map_lock);

	if (result > 0) {
		unsigned int secoff;

		/* Calculate sector offset into map block */
		secoff = offset - signed_asl(mapoff, asb->s_map2blk);
		return secoff + signed_asl(result, asb->s_map2blk);
	}

	adfs_error(sb, "fragment 0x%04x at offset %d not found in map",
		   frag_id, offset);
	return 0;

bad_fragment:
	adfs_error(sb, "invalid fragment 0x%04x (zone = %d, max = %d)",
		   frag_id, zone, asb->s_map_size);
	return 0;
}