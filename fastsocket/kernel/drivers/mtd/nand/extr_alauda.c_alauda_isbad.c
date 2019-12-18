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
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int alauda_read_oob (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int popcount8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alauda_isbad(struct mtd_info *mtd, loff_t ofs)
{
	u8 oob[16];
	int err;

	err = alauda_read_oob(mtd, ofs, oob);
	if (err)
		return err;

	/* A block is marked bad if two or more bits are zero */
	return popcount8(oob[5]) >= 7 ? 0 : 1;
}