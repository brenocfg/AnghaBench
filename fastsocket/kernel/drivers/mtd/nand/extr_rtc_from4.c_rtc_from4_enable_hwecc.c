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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  NAND_ECC_READ 130 
#define  NAND_ECC_READSYN 129 
#define  NAND_ECC_WRITE 128 
 scalar_t__ RTC_FROM4_RS_ECC_CTL ; 
 unsigned short RTC_FROM4_RS_ECC_CTL_CLR ; 
 unsigned short RTC_FROM4_RS_ECC_CTL_FD_E ; 
 unsigned short RTC_FROM4_RS_ECC_CTL_GEN ; 
 scalar_t__ rtc_from4_fio_base ; 

__attribute__((used)) static void rtc_from4_enable_hwecc(struct mtd_info *mtd, int mode)
{
	volatile unsigned short *rs_ecc_ctl = (volatile unsigned short *)(rtc_from4_fio_base + RTC_FROM4_RS_ECC_CTL);
	unsigned short status;

	switch (mode) {
	case NAND_ECC_READ:
		status = RTC_FROM4_RS_ECC_CTL_CLR | RTC_FROM4_RS_ECC_CTL_FD_E;

		*rs_ecc_ctl = status;
		break;

	case NAND_ECC_READSYN:
		status = 0x00;

		*rs_ecc_ctl = status;
		break;

	case NAND_ECC_WRITE:
		status = RTC_FROM4_RS_ECC_CTL_CLR | RTC_FROM4_RS_ECC_CTL_GEN | RTC_FROM4_RS_ECC_CTL_FD_E;

		*rs_ecc_ctl = status;
		break;

	default:
		BUG();
		break;
	}

}