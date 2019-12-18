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
typedef  int u8 ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int OXYGEN_SPI_BUSY ; 
 int /*<<< orphan*/  OXYGEN_SPI_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_SPI_DATA1 ; 
 int /*<<< orphan*/  OXYGEN_SPI_DATA2 ; 
 int /*<<< orphan*/  OXYGEN_SPI_DATA3 ; 
 int OXYGEN_SPI_DATA_LENGTH_3 ; 
 int oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write8 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void oxygen_write_spi(struct oxygen *chip, u8 control, unsigned int data)
{
	unsigned int count;

	/* should not need more than 30.72 us (24 * 1.28 us) */
	count = 10;
	while ((oxygen_read8(chip, OXYGEN_SPI_CONTROL) & OXYGEN_SPI_BUSY)
	       && count > 0) {
		udelay(4);
		--count;
	}

	oxygen_write8(chip, OXYGEN_SPI_DATA1, data);
	oxygen_write8(chip, OXYGEN_SPI_DATA2, data >> 8);
	if (control & OXYGEN_SPI_DATA_LENGTH_3)
		oxygen_write8(chip, OXYGEN_SPI_DATA3, data >> 16);
	oxygen_write8(chip, OXYGEN_SPI_CONTROL, control);
}