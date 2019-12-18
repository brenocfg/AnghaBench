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
 int /*<<< orphan*/  bfin_write_NFC_DATA_WR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bf5xx_nand_write_buf16(struct mtd_info *mtd,
				const uint8_t *buf, int len)
{
	int i;
	u16 *p = (u16 *) buf;
	len >>= 1;

	for (i = 0; i < len; i++)
		bfin_write_NFC_DATA_WR(p[i]);

	SSYNC();
}