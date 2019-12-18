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
struct comedi_cmd {int /*<<< orphan*/  chanlist_len; int /*<<< orphan*/  scan_end_arg; int /*<<< orphan*/  stop_arg; int /*<<< orphan*/  scan_end_src; int /*<<< orphan*/  stop_src; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/  start_arg; int /*<<< orphan*/  convert_src; int /*<<< orphan*/  scan_begin_src; int /*<<< orphan*/  start_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void pcl816_cmdtest_out(int e, struct comedi_cmd *cmd)
{
	printk("pcl816 e=%d startsrc=%x scansrc=%x convsrc=%x\n", e,
	       cmd->start_src, cmd->scan_begin_src, cmd->convert_src);
	printk("pcl816 e=%d startarg=%d scanarg=%d convarg=%d\n", e,
	       cmd->start_arg, cmd->scan_begin_arg, cmd->convert_arg);
	printk("pcl816 e=%d stopsrc=%x scanend=%x\n", e, cmd->stop_src,
	       cmd->scan_end_src);
	printk("pcl816 e=%d stoparg=%d scanendarg=%d chanlistlen=%d\n", e,
	       cmd->stop_arg, cmd->scan_end_arg, cmd->chanlist_len);
}