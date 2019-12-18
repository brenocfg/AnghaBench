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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u16 ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  bfin_read_NFC_READ () ; 
 int /*<<< orphan*/  bfin_write_NFC_DATA_RD (int) ; 

__attribute__((used)) static void bf5xx_nand_read_buf16(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int i;
	u16 *p = (u16 *) buf;
	len >>= 1;

	/*
	 * Data reads are requested by first writing to NFC_DATA_RD
	 * and then reading back from NFC_READ.
	 */
	bfin_write_NFC_DATA_RD(0x5555);

	SSYNC();

	for (i = 0; i < len; i++)
		p[i] = bfin_read_NFC_READ();
}