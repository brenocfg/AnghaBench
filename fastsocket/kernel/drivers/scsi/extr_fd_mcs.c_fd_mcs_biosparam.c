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
struct scsi_device {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* scsi_bios_ptable (struct block_device*) ; 

__attribute__((used)) static int fd_mcs_biosparam(struct scsi_device * disk, struct block_device *bdev,
			    sector_t capacity, int *info_array) 
{
	unsigned char *p = scsi_bios_ptable(bdev);
	int size = capacity;

	/* BIOS >= 3.4 for MCA cards */
	/* This algorithm was provided by Future Domain (much thanks!). */

	if (p && p[65] == 0xaa && p[64] == 0x55	/* Partition table valid */
	    && p[4]) {	/* Partition type */
		/* The partition table layout is as follows:

		   Start: 0x1b3h
		   Offset: 0 = partition status
		   1 = starting head
		   2 = starting sector and cylinder (word, encoded)
		   4 = partition type
		   5 = ending head
		   6 = ending sector and cylinder (word, encoded)
		   8 = starting absolute sector (double word)
		   c = number of sectors (double word)
		   Signature: 0x1fe = 0x55aa

		   So, this algorithm assumes:
		   1) the first partition table is in use,
		   2) the data in the first entry is correct, and
		   3) partitions never divide cylinders

		   Note that (1) may be FALSE for NetBSD (and other BSD flavors),
		   as well as for Linux.  Note also, that Linux doesn't pay any
		   attention to the fields that are used by this algorithm -- it
		   only uses the absolute sector data.  Recent versions of Linux's
		   fdisk(1) will fill this data in correctly, and forthcoming
		   versions will check for consistency.

		   Checking for a non-zero partition type is not part of the
		   Future Domain algorithm, but it seemed to be a reasonable thing
		   to do, especially in the Linux and BSD worlds. */

		info_array[0] = p[5] + 1;	/* heads */
		info_array[1] = p[6] & 0x3f;	/* sectors */
	} else {
		/* Note that this new method guarantees that there will always be
		   less than 1024 cylinders on a platter.  This is good for drives
		   up to approximately 7.85GB (where 1GB = 1024 * 1024 kB). */
		if ((unsigned int) size >= 0x7e0000U) 
		{
			info_array[0] = 0xff;	/* heads   = 255 */
			info_array[1] = 0x3f;	/* sectors =  63 */
		} else if ((unsigned int) size >= 0x200000U) {
			info_array[0] = 0x80;	/* heads   = 128 */
			info_array[1] = 0x3f;	/* sectors =  63 */
		} else {
			info_array[0] = 0x40;	/* heads   =  64 */
			info_array[1] = 0x20;	/* sectors =  32 */
		}
	}
	/* For both methods, compute the cylinders */
	info_array[2] = (unsigned int) size / (info_array[0] * info_array[1]);
	kfree(p);
	return 0;
}