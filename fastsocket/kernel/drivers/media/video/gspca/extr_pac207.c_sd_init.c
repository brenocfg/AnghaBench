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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pac207_write_reg (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	pac207_write_reg(gspca_dev, 0x41, 0x00);
				/* Bit_0=Image Format,
				 * Bit_1=LED,
				 * Bit_2=Compression test mode enable */
	pac207_write_reg(gspca_dev, 0x0f, 0x00); /* Power Control */

	return 0;
}