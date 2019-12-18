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
typedef  int u_char ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_FROM4_RS_ECCN ; 
 scalar_t__ rtc_from4_fio_base ; 

__attribute__((used)) static void rtc_from4_calculate_ecc(struct mtd_info *mtd, const u_char *dat, u_char *ecc_code)
{
	volatile unsigned short *rs_eccn = (volatile unsigned short *)(rtc_from4_fio_base + RTC_FROM4_RS_ECCN);
	unsigned short value;
	int i;

	for (i = 0; i < 8; i++) {
		value = *rs_eccn;
		ecc_code[i] = (unsigned char)value;
		rs_eccn++;
	}
	ecc_code[7] |= 0x0f;	/* set the last four bits (not used) */
}