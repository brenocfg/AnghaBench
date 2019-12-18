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
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int NCR53c406a_biosparm(struct scsi_device *disk,
                               struct block_device *dev,
			       sector_t capacity, int *info_array)
{
	int size;

	DEB(printk("NCR53c406a_biosparm called\n"));

	size = capacity;
	info_array[0] = 64;	/* heads */
	info_array[1] = 32;	/* sectors */
	info_array[2] = size >> 11;	/* cylinders */
	if (info_array[2] > 1024) {	/* big disk */
		info_array[0] = 255;
		info_array[1] = 63;
		info_array[2] = size / (255 * 63);
	}
	return 0;
}