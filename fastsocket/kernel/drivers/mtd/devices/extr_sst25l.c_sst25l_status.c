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
struct sst25l_flash {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 unsigned char SST25L_CMD_RDSR ; 
 int spi_write_then_read (int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,int) ; 

__attribute__((used)) static int sst25l_status(struct sst25l_flash *flash, int *status)
{
	unsigned char command, response;
	int err;

	command = SST25L_CMD_RDSR;
	err = spi_write_then_read(flash->spi, &command, 1, &response, 1);
	if (err < 0)
		return err;

	*status = response;
	return 0;
}