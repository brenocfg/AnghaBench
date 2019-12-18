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
struct wacom_wac {TYPE_1__* features; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  device_type; } ;

/* Variables and functions */
#define  BAMBOO_PT 152 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
#define  CINTIQ 151 
#define  DTU 150 
#define  GRAPHIRE 149 
#define  INTUOS 148 
#define  INTUOS3 147 
#define  INTUOS3L 146 
#define  INTUOS3S 145 
#define  INTUOS4 144 
#define  INTUOS4L 143 
#define  INTUOS4S 142 
#define  INTUOS5 141 
#define  INTUOS5L 140 
#define  INTUOS5S 139 
#define  PENPARTNER 138 
#define  PL 137 
#define  PTU 136 
#define  TABLETPC 135 
#define  TABLETPC2FG 134 
#define  WACOM_21UX2 133 
#define  WACOM_22HD 132 
#define  WACOM_24HD 131 
#define  WACOM_BEE 130 
#define  WACOM_G4 129 
#define  WACOM_MO 128 
 int /*<<< orphan*/  input_dev_24hd (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_bamboo_pt (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_bee (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_c21ux2 (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_c22hd (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_cintiq (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_g (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_g4 (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_i (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_i3 (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_i3s (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_i4 (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_i4s (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_mo (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_pl (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_pt (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_tpc (struct input_dev*,struct wacom_wac*) ; 
 int /*<<< orphan*/  input_dev_tpc2fg (struct input_dev*,struct wacom_wac*) ; 

void wacom_init_input_dev(struct input_dev *input_dev, struct wacom_wac *wacom_wac)
{
	switch (wacom_wac->features->type) {
		case WACOM_MO:
			input_dev_mo(input_dev, wacom_wac);
		case WACOM_G4:
			input_dev_g4(input_dev, wacom_wac);
			/* fall through */
		case GRAPHIRE:
			input_dev_g(input_dev, wacom_wac);
			break;
		case WACOM_24HD:
			input_dev_24hd(input_dev, wacom_wac);
			break;
		case WACOM_22HD:
			input_dev_c22hd(input_dev, wacom_wac);
			/* fall through */
		case WACOM_21UX2:
			input_dev_c21ux2(input_dev, wacom_wac);
			/* fall through */
		case WACOM_BEE:
			input_dev_bee(input_dev, wacom_wac);
                        /* fall through */
		case INTUOS3:
		case INTUOS3L:
			input_dev_i3(input_dev, wacom_wac);
			/* fall through */
		case INTUOS3S:
			input_dev_i3s(input_dev, wacom_wac);
			/* fall through */
		case INTUOS:
			input_dev_i(input_dev, wacom_wac);
			break;
		case INTUOS5:
		case INTUOS5L:
		case INTUOS4:
		case INTUOS4L:
			input_dev_i4(input_dev, wacom_wac);
			/* fall through */
		case INTUOS5S:
		case INTUOS4S:
			input_dev_i4s(input_dev, wacom_wac);
			input_dev_i(input_dev, wacom_wac);
			break;
		case TABLETPC2FG:
			input_dev_tpc2fg(input_dev, wacom_wac);
			/* fall through */
		case TABLETPC:
			input_dev_tpc(input_dev, wacom_wac);
			if (wacom_wac->features->device_type != BTN_TOOL_PEN)
				break;  /* no need to process stylus stuff */

			/* fall through */
		case PL:
		case PTU:
		case DTU:
			input_dev_pl(input_dev, wacom_wac);
			/* fall through */
		case PENPARTNER:
			input_dev_pt(input_dev, wacom_wac);
			break;
                case CINTIQ:
                        input_dev_cintiq(input_dev, wacom_wac);
                        break;
		case BAMBOO_PT:
			input_dev_bamboo_pt(input_dev, wacom_wac);
			break;
	}
	return;
}