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
struct TYPE_2__ {int /*<<< orphan*/  (* volume_method ) (int,unsigned char) ;int /*<<< orphan*/  (* controller ) (int,unsigned char,unsigned char,short) ;int /*<<< orphan*/  (* panning ) (int,unsigned char,char) ;int /*<<< orphan*/  (* aftertouch ) (int,unsigned char,unsigned char) ;int /*<<< orphan*/  (* set_instr ) (int,unsigned char,unsigned char) ;int /*<<< orphan*/  (* start_note ) (int,unsigned char,unsigned char,unsigned char) ;int /*<<< orphan*/  (* kill_note ) (int,unsigned char,unsigned char,unsigned char) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
#define  SEQ_AFTERTOUCH 134 
#define  SEQ_BALANCE 133 
#define  SEQ_CONTROLLER 132 
#define  SEQ_NOTEOFF 131 
#define  SEQ_NOTEON 130 
#define  SEQ_PGMCHANGE 129 
#define  SEQ_VOLMODE 128 
 int max_synthdev ; 
 int /*<<< orphan*/  stub1 (int,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub2 (int,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub3 (int,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub4 (int,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub5 (int,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  stub6 (int,unsigned char,char) ; 
 int /*<<< orphan*/  stub7 (int,unsigned char,unsigned char,short) ; 
 int /*<<< orphan*/  stub8 (int,unsigned char) ; 
 TYPE_1__** synth_devs ; 
 int synth_open_mask ; 

__attribute__((used)) static int extended_event(unsigned char *q)
{
	int dev = q[2];

	if (dev < 0 || dev >= max_synthdev)
		return -ENXIO;

	if (!(synth_open_mask & (1 << dev)))
		return -ENXIO;

	switch (q[1])
	{
		case SEQ_NOTEOFF:
			synth_devs[dev]->kill_note(dev, q[3], q[4], q[5]);
			break;

		case SEQ_NOTEON:
			if (q[4] > 127 && q[4] != 255)
				return 0;

			if (q[5] == 0)
			{
				synth_devs[dev]->kill_note(dev, q[3], q[4], q[5]);
				break;
			}
			synth_devs[dev]->start_note(dev, q[3], q[4], q[5]);
			break;

		case SEQ_PGMCHANGE:
			synth_devs[dev]->set_instr(dev, q[3], q[4]);
			break;

		case SEQ_AFTERTOUCH:
			synth_devs[dev]->aftertouch(dev, q[3], q[4]);
			break;

		case SEQ_BALANCE:
			synth_devs[dev]->panning(dev, q[3], (char) q[4]);
			break;

		case SEQ_CONTROLLER:
			synth_devs[dev]->controller(dev, q[3], q[4], (short) (q[5] | (q[6] << 8)));
			break;

		case SEQ_VOLMODE:
			if (synth_devs[dev]->volume_method != NULL)
				synth_devs[dev]->volume_method(dev, q[3]);
			break;

		default:
			return -EINVAL;
	}
	return 0;
}