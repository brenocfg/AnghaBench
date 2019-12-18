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
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_line_high ; 
 int /*<<< orphan*/  i2c_line_low ; 
 int /*<<< orphan*/  scl_out (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sda_out (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_ack(struct ipath_devdata *dd)
{
	sda_out(dd, i2c_line_low);
	scl_out(dd, i2c_line_high);
	scl_out(dd, i2c_line_low);
	sda_out(dd, i2c_line_high);
}