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
struct blk_integrity {int sector_size; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int bio_integrity_hw_sectors(struct blk_integrity *bi,
						    unsigned int sectors)
{
	/* At this point there are only 512b or 4096b DIF/EPP devices */
	if (bi->sector_size == 4096)
		return sectors >>= 3;

	return sectors;
}