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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct lun {int num_sectors; int /*<<< orphan*/  sense_data; } ;
struct fsg_dev {int* cmnd; struct lun* curlun; } ;
struct fsg_buffhd {scalar_t__ buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SS_INVALID_FIELD_IN_CDB ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_read_capacity(struct fsg_dev *fsg, struct fsg_buffhd *bh)
{
	struct lun	*curlun = fsg->curlun;
	u32		lba = get_unaligned_be32(&fsg->cmnd[2]);
	int		pmi = fsg->cmnd[8];
	u8		*buf = (u8 *) bh->buf;

	/* Check the PMI and LBA fields */
	if (pmi > 1 || (pmi == 0 && lba != 0)) {
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		return -EINVAL;
	}

	put_unaligned_be32(curlun->num_sectors - 1, &buf[0]);
						/* Max logical block */
	put_unaligned_be32(512, &buf[4]);	/* Block length */
	return 8;
}