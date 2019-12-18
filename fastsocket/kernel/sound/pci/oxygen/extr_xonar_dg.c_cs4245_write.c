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
typedef  unsigned int u8 ;
struct oxygen {struct dg* model_data; } ;
struct dg {unsigned int* cs4245_regs; } ;

/* Variables and functions */
 unsigned int CS4245_SPI_ADDRESS ; 
 unsigned int CS4245_SPI_WRITE ; 
 int OXYGEN_SPI_CEN_LATCH_CLOCK_HI ; 
 int OXYGEN_SPI_CLOCK_1280 ; 
 int OXYGEN_SPI_CODEC_SHIFT ; 
 int OXYGEN_SPI_DATA_LENGTH_3 ; 
 int OXYGEN_SPI_TRIGGER ; 
 int /*<<< orphan*/  oxygen_write_spi (struct oxygen*,int,unsigned int) ; 

__attribute__((used)) static void cs4245_write(struct oxygen *chip, unsigned int reg, u8 value)
{
	struct dg *data = chip->model_data;

	oxygen_write_spi(chip, OXYGEN_SPI_TRIGGER |
			 OXYGEN_SPI_DATA_LENGTH_3 |
			 OXYGEN_SPI_CLOCK_1280 |
			 (0 << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_LATCH_CLOCK_HI,
			 CS4245_SPI_ADDRESS |
			 CS4245_SPI_WRITE |
			 (reg << 8) | value);
	data->cs4245_regs[reg] = value;
}