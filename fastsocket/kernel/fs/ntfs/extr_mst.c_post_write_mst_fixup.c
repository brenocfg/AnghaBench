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
typedef  int u16 ;
typedef  int /*<<< orphan*/  le16 ;
struct TYPE_3__ {int /*<<< orphan*/  usa_count; int /*<<< orphan*/  usa_ofs; } ;
typedef  TYPE_1__ NTFS_RECORD ;

/* Variables and functions */
 int NTFS_BLOCK_SIZE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

void post_write_mst_fixup(NTFS_RECORD *b)
{
	le16 *usa_pos, *data_pos;

	u16 usa_ofs = le16_to_cpu(b->usa_ofs);
	u16 usa_count = le16_to_cpu(b->usa_count) - 1;

	/* Position of usn in update sequence array. */
	usa_pos = (le16*)b + usa_ofs/sizeof(le16);

	/* Position in protected data of first u16 that needs fixing up. */
	data_pos = (le16*)b + NTFS_BLOCK_SIZE/sizeof(le16) - 1;

	/* Fixup all sectors. */
	while (usa_count--) {
		/*
		 * Increment position in usa and restore original data from
		 * the usa into the data buffer.
		 */
		*data_pos = *(++usa_pos);

		/* Increment position in data as well. */
		data_pos += NTFS_BLOCK_SIZE/sizeof(le16);
	}
}