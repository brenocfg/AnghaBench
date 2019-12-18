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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct lun {scalar_t__ num_sectors; int /*<<< orphan*/  sense_data; } ;
struct fsg_dev {int* cmnd; struct lun* curlun; } ;
struct fsg_buffhd {scalar_t__ buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SS_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE ; 
 scalar_t__ get_unaligned_be32 (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_cdrom_address (int*,int,scalar_t__) ; 

__attribute__((used)) static int do_read_header(struct fsg_dev *fsg, struct fsg_buffhd *bh)
{
	struct lun	*curlun = fsg->curlun;
	int		msf = fsg->cmnd[1] & 0x02;
	u32		lba = get_unaligned_be32(&fsg->cmnd[2]);
	u8		*buf = (u8 *) bh->buf;

	if ((fsg->cmnd[1] & ~0x02) != 0) {		/* Mask away MSF */
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		return -EINVAL;
	}
	if (lba >= curlun->num_sectors) {
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		return -EINVAL;
	}

	memset(buf, 0, 8);
	buf[0] = 0x01;		/* 2048 bytes of user data, rest is EC */
	store_cdrom_address(&buf[4], msf, lba);
	return 8;
}