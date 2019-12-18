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
typedef  int /*<<< orphan*/  uchar ;
struct IN2000_hostdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_WD_ADDR ; 
 int /*<<< orphan*/  IO_WD_DATA ; 
 int /*<<< orphan*/  WD_COMMAND ; 
 int /*<<< orphan*/  write1_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void write_3393_cmd(struct IN2000_hostdata *hostdata, uchar cmd)
{
/*   while (READ_AUX_STAT() & ASR_CIP)
      printk("|");*/
	write1_io(WD_COMMAND, IO_WD_ADDR);
	write1_io(cmd, IO_WD_DATA);
}