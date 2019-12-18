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
 int /*<<< orphan*/  TG_GPODR2 ; 
 int tosa_tg_send (struct spi_device*,int /*<<< orphan*/ ,int) ; 

int tosa_bl_enable(struct spi_device *spi, int enable)
{
	/* bl_enable GP04=1 otherwise GP04=0*/
	return tosa_tg_send(spi, TG_GPODR2, enable? 0x01 : 0x00);
}