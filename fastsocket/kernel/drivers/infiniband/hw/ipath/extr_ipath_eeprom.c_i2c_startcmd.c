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
typedef  int /*<<< orphan*/  u8 ;
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  i2c_line_high ; 
 int /*<<< orphan*/  i2c_line_low ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scl_out (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sda_out (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int wr_byte (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_startcmd(struct ipath_devdata *dd, u8 offset_dir)
{
	int res;

	/* issue start sequence */
	sda_out(dd, i2c_line_high);
	scl_out(dd, i2c_line_high);
	sda_out(dd, i2c_line_low);
	scl_out(dd, i2c_line_low);

	/* issue length and direction byte */
	res = wr_byte(dd, offset_dir);

	if (res)
		ipath_cdbg(VERBOSE, "No ack to complete start\n");

	return res;
}