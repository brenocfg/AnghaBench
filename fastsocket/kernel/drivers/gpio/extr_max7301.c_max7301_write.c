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
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u16 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int spi_write (struct spi_device*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int max7301_write(struct spi_device *spi, unsigned int reg, unsigned int val)
{
	u16 word = ((reg & 0x7F) << 8) | (val & 0xFF);
	return spi_write(spi, (const u8 *)&word, sizeof(word));
}