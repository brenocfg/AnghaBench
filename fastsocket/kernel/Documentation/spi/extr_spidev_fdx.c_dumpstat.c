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
typedef  int __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_IOC_RD_BITS_PER_WORD ; 
 int /*<<< orphan*/  SPI_IOC_RD_LSB_FIRST ; 
 int /*<<< orphan*/  SPI_IOC_RD_MAX_SPEED_HZ ; 
 int /*<<< orphan*/  SPI_IOC_RD_MODE ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,int,char*,int) ; 

__attribute__((used)) static void dumpstat(const char *name, int fd)
{
	__u8	mode, lsb, bits;
	__u32	speed;

	if (ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0) {
		perror("SPI rd_mode");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
		perror("SPI rd_lsb_fist");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
		perror("SPI bits_per_word");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
		perror("SPI max_speed_hz");
		return;
	}

	printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n",
		name, mode, bits, lsb ? "(lsb first) " : "", speed);
}