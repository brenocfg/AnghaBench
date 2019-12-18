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
struct partition {int cyl; int sector; int end_cyl; int end_sector; int end_head; int /*<<< orphan*/  nr_sects; int /*<<< orphan*/  start_sect; int /*<<< orphan*/  sys_ind; } ;

/* Variables and functions */
 unsigned int get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,...) ; 

int scsi_partsize(unsigned char *buf, unsigned long capacity,
	       unsigned int *cyls, unsigned int *hds, unsigned int *secs)
{
	struct partition *p = (struct partition *)buf, *largest = NULL;
	int i, largest_cyl;
	int cyl, ext_cyl, end_head, end_cyl, end_sector;
	unsigned int logical_end, physical_end, ext_physical_end;


	if (*(unsigned short *) (buf + 64) == 0xAA55) {
		for (largest_cyl = -1, i = 0; i < 4; ++i, ++p) {
			if (!p->sys_ind)
				continue;
#ifdef DEBUG
			printk("scsicam_bios_param : partition %d has system \n",
			       i);
#endif
			cyl = p->cyl + ((p->sector & 0xc0) << 2);
			if (cyl > largest_cyl) {
				largest_cyl = cyl;
				largest = p;
			}
		}
	}
	if (largest) {
		end_cyl = largest->end_cyl + ((largest->end_sector & 0xc0) << 2);
		end_head = largest->end_head;
		end_sector = largest->end_sector & 0x3f;

		if (end_head + 1 == 0 || end_sector == 0)
			return -1;

#ifdef DEBUG
		printk("scsicam_bios_param : end at h = %d, c = %d, s = %d\n",
		       end_head, end_cyl, end_sector);
#endif

		physical_end = end_cyl * (end_head + 1) * end_sector +
		    end_head * end_sector + end_sector;

		/* This is the actual _sector_ number at the end */
		logical_end = get_unaligned(&largest->start_sect)
		    + get_unaligned(&largest->nr_sects);

		/* This is for >1023 cylinders */
		ext_cyl = (logical_end - (end_head * end_sector + end_sector))
		    / (end_head + 1) / end_sector;
		ext_physical_end = ext_cyl * (end_head + 1) * end_sector +
		    end_head * end_sector + end_sector;

#ifdef DEBUG
		printk("scsicam_bios_param : logical_end=%d physical_end=%d ext_physical_end=%d ext_cyl=%d\n"
		  ,logical_end, physical_end, ext_physical_end, ext_cyl);
#endif

		if ((logical_end == physical_end) ||
		  (end_cyl == 1023 && ext_physical_end == logical_end)) {
			*secs = end_sector;
			*hds = end_head + 1;
			*cyls = capacity / ((end_head + 1) * end_sector);
			return 0;
		}
#ifdef DEBUG
		printk("scsicam_bios_param : logical (%u) != physical (%u)\n",
		       logical_end, physical_end);
#endif
	}
	return -1;
}