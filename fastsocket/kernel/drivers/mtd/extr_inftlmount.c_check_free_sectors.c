#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mtd_info {int oobsize; scalar_t__ (* read ) (struct mtd_info*,unsigned int,int,size_t*,int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {struct mtd_info* mtd; } ;
struct INFTLrecord {TYPE_1__ mbd; } ;

/* Variables and functions */
 int SECTORSIZE ; 
 scalar_t__ inftl_read_oob (struct mtd_info*,unsigned int,int,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmpb (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ stub1 (struct mtd_info*,unsigned int,int,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_free_sectors(struct INFTLrecord *inftl, unsigned int address,
	int len, int check_oob)
{
	u8 buf[SECTORSIZE + inftl->mbd.mtd->oobsize];
	struct mtd_info *mtd = inftl->mbd.mtd;
	size_t retlen;
	int i;

	for (i = 0; i < len; i += SECTORSIZE) {
		if (mtd->read(mtd, address, SECTORSIZE, &retlen, buf))
			return -1;
		if (memcmpb(buf, 0xff, SECTORSIZE) != 0)
			return -1;

		if (check_oob) {
			if(inftl_read_oob(mtd, address, mtd->oobsize,
					  &retlen, &buf[SECTORSIZE]) < 0)
				return -1;
			if (memcmpb(buf + SECTORSIZE, 0xff, mtd->oobsize) != 0)
				return -1;
		}
		address += SECTORSIZE;
	}

	return 0;
}