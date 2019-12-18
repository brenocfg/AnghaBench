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

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SPI_IOC_RD_BITS_PER_WORD ; 
 int /*<<< orphan*/  SPI_IOC_RD_MAX_SPEED_HZ ; 
 int /*<<< orphan*/  SPI_IOC_RD_MODE ; 
 int /*<<< orphan*/  SPI_IOC_WR_BITS_PER_WORD ; 
 int /*<<< orphan*/  SPI_IOC_WR_MAX_SPEED_HZ ; 
 int /*<<< orphan*/  SPI_IOC_WR_MODE ; 
 int bits ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  device ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int mode ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pabort (char*) ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int speed ; 
 int /*<<< orphan*/  transfer (int) ; 

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd;

	parse_opts(argc, argv);

	fd = open(device, O_RDWR);
	if (fd < 0)
		pabort("can't open device");

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		pabort("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		pabort("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't get max speed hz");

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

	transfer(fd);

	close(fd);

	return ret;
}