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
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_ackrcv (struct ipath_devdata*) ; 
 int /*<<< orphan*/  i2c_line_high ; 
 int /*<<< orphan*/  i2c_line_low ; 
 int /*<<< orphan*/  scl_out (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sda_out (struct ipath_devdata*,int) ; 

__attribute__((used)) static int wr_byte(struct ipath_devdata *dd, u8 data)
{
	int bit_cntr;
	u8 bit;

	for (bit_cntr = 7; bit_cntr >= 0; bit_cntr--) {
		bit = (data >> bit_cntr) & 1;
		sda_out(dd, bit);
		scl_out(dd, i2c_line_high);
		scl_out(dd, i2c_line_low);
	}
	return (!i2c_ackrcv(dd)) ? 1 : 0;
}