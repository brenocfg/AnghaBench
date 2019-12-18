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
struct IN2000_hostdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_WD_ADDR ; 
 int /*<<< orphan*/  IO_WD_DATA ; 
 unsigned long WD_TRANSFER_COUNT_MSB ; 
 int /*<<< orphan*/  write1_io (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_3393_count(struct IN2000_hostdata *hostdata, unsigned long value)
{
	write1_io(WD_TRANSFER_COUNT_MSB, IO_WD_ADDR);
	write1_io((value >> 16), IO_WD_DATA);
	write1_io((value >> 8), IO_WD_DATA);
	write1_io(value, IO_WD_DATA);
}