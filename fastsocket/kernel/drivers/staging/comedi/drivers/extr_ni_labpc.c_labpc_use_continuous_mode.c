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
struct comedi_cmd {scalar_t__ scan_begin_src; } ;

/* Variables and functions */
 scalar_t__ MODE_SINGLE_CHAN ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ labpc_ai_scan_mode (struct comedi_cmd const*) ; 

__attribute__((used)) static int labpc_use_continuous_mode(const struct comedi_cmd *cmd)
{
	if (labpc_ai_scan_mode(cmd) == MODE_SINGLE_CHAN)
		return 1;

	if (cmd->scan_begin_src == TRIG_FOLLOW)
		return 1;

	return 0;
}