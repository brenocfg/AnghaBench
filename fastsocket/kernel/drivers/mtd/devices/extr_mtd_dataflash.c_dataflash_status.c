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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_READ_STATUS ; 
 int spi_w8r8 (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dataflash_status(struct spi_device *spi)
{
	/* NOTE:  at45db321c over 25 MHz wants to write
	 * a dummy byte after the opcode...
	 */
	return spi_w8r8(spi, OP_READ_STATUS);
}