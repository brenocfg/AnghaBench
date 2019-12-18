#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long long mft_zone_multiplier; int nr_clusters; scalar_t__ mft_zone_start; scalar_t__ mft_zone_pos; scalar_t__ mft_lcn; int cluster_size; scalar_t__ mft_zone_end; scalar_t__ data1_zone_pos; int mft_data_pos; scalar_t__ data2_zone_pos; } ;
typedef  TYPE_1__ ntfs_volume ;
typedef  int LCN ;

/* Variables and functions */
 int /*<<< orphan*/  ntfs_debug (char*,unsigned long long) ; 

__attribute__((used)) static void ntfs_setup_allocators(ntfs_volume *vol)
{
#ifdef NTFS_RW
	LCN mft_zone_size, mft_lcn;
#endif /* NTFS_RW */

	ntfs_debug("vol->mft_zone_multiplier = 0x%x",
			vol->mft_zone_multiplier);
#ifdef NTFS_RW
	/* Determine the size of the MFT zone. */
	mft_zone_size = vol->nr_clusters;
	switch (vol->mft_zone_multiplier) {  /* % of volume size in clusters */
	case 4:
		mft_zone_size >>= 1;			/* 50%   */
		break;
	case 3:
		mft_zone_size = (mft_zone_size +
				(mft_zone_size >> 1)) >> 2;	/* 37.5% */
		break;
	case 2:
		mft_zone_size >>= 2;			/* 25%   */
		break;
	/* case 1: */
	default:
		mft_zone_size >>= 3;			/* 12.5% */
		break;
	}
	/* Setup the mft zone. */
	vol->mft_zone_start = vol->mft_zone_pos = vol->mft_lcn;
	ntfs_debug("vol->mft_zone_pos = 0x%llx",
			(unsigned long long)vol->mft_zone_pos);
	/*
	 * Calculate the mft_lcn for an unmodified NTFS volume (see mkntfs
	 * source) and if the actual mft_lcn is in the expected place or even
	 * further to the front of the volume, extend the mft_zone to cover the
	 * beginning of the volume as well.  This is in order to protect the
	 * area reserved for the mft bitmap as well within the mft_zone itself.
	 * On non-standard volumes we do not protect it as the overhead would
	 * be higher than the speed increase we would get by doing it.
	 */
	mft_lcn = (8192 + 2 * vol->cluster_size - 1) / vol->cluster_size;
	if (mft_lcn * vol->cluster_size < 16 * 1024)
		mft_lcn = (16 * 1024 + vol->cluster_size - 1) /
				vol->cluster_size;
	if (vol->mft_zone_start <= mft_lcn)
		vol->mft_zone_start = 0;
	ntfs_debug("vol->mft_zone_start = 0x%llx",
			(unsigned long long)vol->mft_zone_start);
	/*
	 * Need to cap the mft zone on non-standard volumes so that it does
	 * not point outside the boundaries of the volume.  We do this by
	 * halving the zone size until we are inside the volume.
	 */
	vol->mft_zone_end = vol->mft_lcn + mft_zone_size;
	while (vol->mft_zone_end >= vol->nr_clusters) {
		mft_zone_size >>= 1;
		vol->mft_zone_end = vol->mft_lcn + mft_zone_size;
	}
	ntfs_debug("vol->mft_zone_end = 0x%llx",
			(unsigned long long)vol->mft_zone_end);
	/*
	 * Set the current position within each data zone to the start of the
	 * respective zone.
	 */
	vol->data1_zone_pos = vol->mft_zone_end;
	ntfs_debug("vol->data1_zone_pos = 0x%llx",
			(unsigned long long)vol->data1_zone_pos);
	vol->data2_zone_pos = 0;
	ntfs_debug("vol->data2_zone_pos = 0x%llx",
			(unsigned long long)vol->data2_zone_pos);

	/* Set the mft data allocation position to mft record 24. */
	vol->mft_data_pos = 24;
	ntfs_debug("vol->mft_data_pos = 0x%llx",
			(unsigned long long)vol->mft_data_pos);
#endif /* NTFS_RW */
}