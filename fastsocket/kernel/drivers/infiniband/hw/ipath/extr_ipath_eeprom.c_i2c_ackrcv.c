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
 int /*<<< orphan*/  i2c_line_high ; 
 int /*<<< orphan*/  i2c_line_low ; 
 int /*<<< orphan*/  scl_out (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ sda_in (struct ipath_devdata*,int) ; 

__attribute__((used)) static int i2c_ackrcv(struct ipath_devdata *dd)
{
	u8 ack_received;

	/* AT ENTRY SCL = LOW */
	/* change direction, ignore data */
	ack_received = sda_in(dd, 1);
	scl_out(dd, i2c_line_high);
	ack_received = sda_in(dd, 1) == 0;
	scl_out(dd, i2c_line_low);
	return ack_received;
}