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
 int /*<<< orphan*/  WD_TRANSFER_COUNT_MSB ; 
 unsigned long read1_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write1_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long read_3393_count(struct IN2000_hostdata *hostdata)
{
	unsigned long value;

	write1_io(WD_TRANSFER_COUNT_MSB, IO_WD_ADDR);
	value = read1_io(IO_WD_DATA) << 16;
	value |= read1_io(IO_WD_DATA) << 8;
	value |= read1_io(IO_WD_DATA);
	return value;
}