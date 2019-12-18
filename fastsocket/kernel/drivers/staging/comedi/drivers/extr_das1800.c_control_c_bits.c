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
struct comedi_cmd {int scan_begin_src; int /*<<< orphan*/  convert_src; int /*<<< orphan*/ * chanlist; } ;

/* Variables and functions */
 int AREF_COMMON ; 
 int AREF_DIFF ; 
 int BMDE ; 
 int CMEN ; 
 int CR_AREF (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int IPCLK ; 
 int SD ; 
#define  TRIG_EXT 130 
#define  TRIG_FOLLOW 129 
#define  TRIG_TIMER 128 
 int UB ; 
 int UNIPOLAR ; 
 int UQEN ; 
 int XPCLK ; 

__attribute__((used)) static int control_c_bits(struct comedi_cmd cmd)
{
	int control_c;
	int aref;

	/* set clock source to internal or external, select analog reference,
	 * select unipolar / bipolar
	 */
	aref = CR_AREF(cmd.chanlist[0]);
	control_c = UQEN;	/* enable upper qram addresses */
	if (aref != AREF_DIFF)
		control_c |= SD;
	if (aref == AREF_COMMON)
		control_c |= CMEN;
	/* if a unipolar range was selected */
	if (CR_RANGE(cmd.chanlist[0]) & UNIPOLAR)
		control_c |= UB;
	switch (cmd.scan_begin_src) {
	case TRIG_FOLLOW:	/*  not in burst mode */
		switch (cmd.convert_src) {
		case TRIG_TIMER:
			/* trig on cascaded counters */
			control_c |= IPCLK;
			break;
		case TRIG_EXT:
			/* trig on falling edge of external trigger */
			control_c |= XPCLK;
			break;
		default:
			break;
		}
		break;
	case TRIG_TIMER:
		/*  burst mode with internal pacer clock */
		control_c |= BMDE | IPCLK;
		break;
	case TRIG_EXT:
		/*  burst mode with external trigger */
		control_c |= BMDE | XPCLK;
		break;
	default:
		break;
	}

	return control_c;
}