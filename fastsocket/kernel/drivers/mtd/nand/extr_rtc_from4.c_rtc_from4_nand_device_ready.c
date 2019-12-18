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
 unsigned short RTC_FROM4_DEVICE_READY ; 
 scalar_t__ RTC_FROM4_FPGA_SR ; 
 scalar_t__ rtc_from4_fio_base ; 

__attribute__((used)) static int rtc_from4_nand_device_ready(struct mtd_info *mtd)
{
	unsigned short status;

	status = *((volatile unsigned short *)(rtc_from4_fio_base + RTC_FROM4_FPGA_SR));

	return (status & RTC_FROM4_DEVICE_READY);

}