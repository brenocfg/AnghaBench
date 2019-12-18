#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct comedi_cmd {int dummy; } ;
struct TYPE_2__ {int layout; } ;

/* Variables and functions */
#define  LAYOUT_4020 128 
 TYPE_1__* board (struct comedi_device*) ; 
 int /*<<< orphan*/  select_master_clock_4020 (struct comedi_device*,struct comedi_cmd const*) ; 

__attribute__((used)) static void select_master_clock(struct comedi_device *dev,
				const struct comedi_cmd *cmd)
{
	switch (board(dev)->layout) {
	case LAYOUT_4020:
		select_master_clock_4020(dev, cmd);
		break;
	default:
		break;
	}
}