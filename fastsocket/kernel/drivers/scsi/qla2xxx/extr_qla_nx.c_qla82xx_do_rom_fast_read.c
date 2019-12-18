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
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ MD_DIRECT_ROM_READ_BASE ; 
 scalar_t__ MD_DIRECT_ROM_WINDOW ; 
 int qla82xx_md_rw_32 (struct qla_hw_data*,scalar_t__,int,int) ; 

__attribute__((used)) static int
qla82xx_do_rom_fast_read(struct qla_hw_data *ha, int addr, int *valp)
{
	/* Dword reads to flash. */
	qla82xx_md_rw_32(ha, MD_DIRECT_ROM_WINDOW, (addr & 0xFFFF0000), 1);
	*valp = qla82xx_md_rw_32(ha, MD_DIRECT_ROM_READ_BASE +
	    (addr & 0x0000FFFF), 0, 0);

	return 0;
}