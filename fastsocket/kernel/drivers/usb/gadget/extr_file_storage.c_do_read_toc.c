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
struct lun {int /*<<< orphan*/  num_sectors; int /*<<< orphan*/  sense_data; } ;
struct fsg_dev {int* cmnd; struct lun* curlun; } ;
struct fsg_buffhd {scalar_t__ buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SS_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_cdrom_address (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_read_toc(struct fsg_dev *fsg, struct fsg_buffhd *bh)
{
	struct lun	*curlun = fsg->curlun;
	int		msf = fsg->cmnd[1] & 0x02;
	int		start_track = fsg->cmnd[6];
	u8		*buf = (u8 *) bh->buf;

	if ((fsg->cmnd[1] & ~0x02) != 0 ||		/* Mask away MSF */
			start_track > 1) {
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		return -EINVAL;
	}

	memset(buf, 0, 20);
	buf[1] = (20-2);		/* TOC data length */
	buf[2] = 1;			/* First track number */
	buf[3] = 1;			/* Last track number */
	buf[5] = 0x16;			/* Data track, copying allowed */
	buf[6] = 0x01;			/* Only track is number 1 */
	store_cdrom_address(&buf[8], msf, 0);

	buf[13] = 0x16;			/* Lead-out track is data */
	buf[14] = 0xAA;			/* Lead-out track number */
	store_cdrom_address(&buf[16], msf, curlun->num_sectors);
	return 20;
}