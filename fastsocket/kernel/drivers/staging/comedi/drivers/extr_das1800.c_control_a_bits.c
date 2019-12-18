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
struct comedi_cmd {scalar_t__ stop_src; int start_src; } ;

/* Variables and functions */
 int ATEN ; 
 int CGEN ; 
 int CGSL ; 
 int FFEN ; 
 int TGEN ; 
#define  TRIG_EXT 129 
#define  TRIG_NOW 128 

__attribute__((used)) static int control_a_bits(struct comedi_cmd cmd)
{
	int control_a;

	control_a = FFEN;	/* enable fifo */
	if (cmd.stop_src == TRIG_EXT) {
		control_a |= ATEN;
	}
	switch (cmd.start_src) {
	case TRIG_EXT:
		control_a |= TGEN | CGSL;
		break;
	case TRIG_NOW:
		control_a |= CGEN;
		break;
	default:
		break;
	}

	return control_a;
}