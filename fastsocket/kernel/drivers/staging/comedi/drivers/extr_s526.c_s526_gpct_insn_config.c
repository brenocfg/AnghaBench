#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int coutPolarity; int autoLoadResetRcap; int hwCtEnableSource; int ctEnableCtrl; int clockSource; int countDir; int countDirCtrl; int preloadRegSel; int /*<<< orphan*/  reserved; int /*<<< orphan*/  outputRegLatchCtrl; int /*<<< orphan*/  coutSource; } ;
union cmReg {short value; TYPE_2__ reg; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int* data; int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* s526_gpct_config; } ;
struct TYPE_4__ {int* data; int /*<<< orphan*/  app; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_CHAN_REG (int /*<<< orphan*/ ,int) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int GPCT_IndexPhaseHighHigh ; 
 int GPCT_IndexPhaseHighLow ; 
 int GPCT_IndexPhaseLowHigh ; 
 int GPCT_IndexPhaseLowLow ; 
 int GPCT_RESET_COUNTER_ON_INDEX ; 
 int GPCT_X2 ; 
 int GPCT_X4 ; 
#define  INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR 130 
#define  INSN_CONFIG_GPCT_QUADRATURE_ENCODER 129 
#define  INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR 128 
 int MAX_GPCT_CONFIG_DATA ; 
 int /*<<< orphan*/  PositionMeasurement ; 
 int /*<<< orphan*/  PulseTrainGeneration ; 
 int /*<<< orphan*/  REG_C0C ; 
 int /*<<< orphan*/  REG_C0H ; 
 int /*<<< orphan*/  REG_C0L ; 
 int /*<<< orphan*/  REG_C0M ; 
 int /*<<< orphan*/  SinglePulseGeneration ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  outw (short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int s526_gpct_insn_config(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	int subdev_channel = CR_CHAN(insn->chanspec);	/*  Unpack chanspec */
	int i;
	short value;
	union cmReg cmReg;

/* printk("s526: GPCT_INSN_CONFIG: Configuring Channel %d\n", subdev_channel); */

	for (i = 0; i < MAX_GPCT_CONFIG_DATA; i++) {
		devpriv->s526_gpct_config[subdev_channel].data[i] =
		    insn->data[i];
/* printk("data[%d]=%x\n", i, insn->data[i]); */
	}

	/*  Check what type of Counter the user requested, data[0] contains */
	/*  the Application type */
	switch (insn->data[0]) {
	case INSN_CONFIG_GPCT_QUADRATURE_ENCODER:
		/*
		   data[0]: Application Type
		   data[1]: Counter Mode Register Value
		   data[2]: Pre-load Register Value
		   data[3]: Conter Control Register
		 */
		printk("s526: GPCT_INSN_CONFIG: Configuring Encoder\n");
		devpriv->s526_gpct_config[subdev_channel].app =
		    PositionMeasurement;

#if 0
		/*  Example of Counter Application */
		/* One-shot (software trigger) */
		cmReg.reg.coutSource = 0;	/*  out RCAP */
		cmReg.reg.coutPolarity = 1;	/*  Polarity inverted */
		cmReg.reg.autoLoadResetRcap = 0;	/*  Auto load disabled */
		cmReg.reg.hwCtEnableSource = 3;	/*  NOT RCAP */
		cmReg.reg.ctEnableCtrl = 2;	/*  Hardware */
		cmReg.reg.clockSource = 2;	/*  Internal */
		cmReg.reg.countDir = 1;	/*  Down */
		cmReg.reg.countDirCtrl = 1;	/*  Software */
		cmReg.reg.outputRegLatchCtrl = 0;	/*  latch on read */
		cmReg.reg.preloadRegSel = 0;	/*  PR0 */
		cmReg.reg.reserved = 0;

		outw(cmReg.value, ADDR_CHAN_REG(REG_C0M, subdev_channel));

		outw(0x0001, ADDR_CHAN_REG(REG_C0H, subdev_channel));
		outw(0x3C68, ADDR_CHAN_REG(REG_C0L, subdev_channel));

		outw(0x8000, ADDR_CHAN_REG(REG_C0C, subdev_channel));	/*  Reset the counter */
		outw(0x4000, ADDR_CHAN_REG(REG_C0C, subdev_channel));	/*  Load the counter from PR0 */

		outw(0x0008, ADDR_CHAN_REG(REG_C0C, subdev_channel));	/*  Reset RCAP (fires one-shot) */

#endif

#if 1
		/*  Set Counter Mode Register */
		cmReg.value = insn->data[1] & 0xFFFF;

/* printk("s526: Counter Mode register=%x\n", cmReg.value); */
		outw(cmReg.value, ADDR_CHAN_REG(REG_C0M, subdev_channel));

		/*  Reset the counter if it is software preload */
		if (cmReg.reg.autoLoadResetRcap == 0) {
			outw(0x8000, ADDR_CHAN_REG(REG_C0C, subdev_channel));	/*  Reset the counter */
/* outw(0x4000, ADDR_CHAN_REG(REG_C0C, subdev_channel));    Load the counter from PR0 */
		}
#else
		cmReg.reg.countDirCtrl = 0;	/*  0 quadrature, 1 software control */

		/*  data[1] contains GPCT_X1, GPCT_X2 or GPCT_X4 */
		if (insn->data[1] == GPCT_X2) {
			cmReg.reg.clockSource = 1;
		} else if (insn->data[1] == GPCT_X4) {
			cmReg.reg.clockSource = 2;
		} else {
			cmReg.reg.clockSource = 0;
		}

		/*  When to take into account the indexpulse: */
		if (insn->data[2] == GPCT_IndexPhaseLowLow) {
		} else if (insn->data[2] == GPCT_IndexPhaseLowHigh) {
		} else if (insn->data[2] == GPCT_IndexPhaseHighLow) {
		} else if (insn->data[2] == GPCT_IndexPhaseHighHigh) {
		}
		/*  Take into account the index pulse? */
		if (insn->data[3] == GPCT_RESET_COUNTER_ON_INDEX)
			cmReg.reg.autoLoadResetRcap = 4;	/*  Auto load with INDEX^ */

		/*  Set Counter Mode Register */
		cmReg.value = (short)(insn->data[1] & 0xFFFF);
		outw(cmReg.value, ADDR_CHAN_REG(REG_C0M, subdev_channel));

		/*  Load the pre-load register high word */
		value = (short)((insn->data[2] >> 16) & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0H, subdev_channel));

		/*  Load the pre-load register low word */
		value = (short)(insn->data[2] & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0L, subdev_channel));

		/*  Write the Counter Control Register */
		if (insn->data[3] != 0) {
			value = (short)(insn->data[3] & 0xFFFF);
			outw(value, ADDR_CHAN_REG(REG_C0C, subdev_channel));
		}
		/*  Reset the counter if it is software preload */
		if (cmReg.reg.autoLoadResetRcap == 0) {
			outw(0x8000, ADDR_CHAN_REG(REG_C0C, subdev_channel));	/*  Reset the counter */
			outw(0x4000, ADDR_CHAN_REG(REG_C0C, subdev_channel));	/*  Load the counter from PR0 */
		}
#endif
		break;

	case INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR:
		/*
		   data[0]: Application Type
		   data[1]: Counter Mode Register Value
		   data[2]: Pre-load Register 0 Value
		   data[3]: Pre-load Register 1 Value
		   data[4]: Conter Control Register
		 */
		printk("s526: GPCT_INSN_CONFIG: Configuring SPG\n");
		devpriv->s526_gpct_config[subdev_channel].app =
		    SinglePulseGeneration;

		/*  Set Counter Mode Register */
		cmReg.value = (short)(insn->data[1] & 0xFFFF);
		cmReg.reg.preloadRegSel = 0;	/*  PR0 */
		outw(cmReg.value, ADDR_CHAN_REG(REG_C0M, subdev_channel));

		/*  Load the pre-load register 0 high word */
		value = (short)((insn->data[2] >> 16) & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0H, subdev_channel));

		/*  Load the pre-load register 0 low word */
		value = (short)(insn->data[2] & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0L, subdev_channel));

		/*  Set Counter Mode Register */
		cmReg.value = (short)(insn->data[1] & 0xFFFF);
		cmReg.reg.preloadRegSel = 1;	/*  PR1 */
		outw(cmReg.value, ADDR_CHAN_REG(REG_C0M, subdev_channel));

		/*  Load the pre-load register 1 high word */
		value = (short)((insn->data[3] >> 16) & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0H, subdev_channel));

		/*  Load the pre-load register 1 low word */
		value = (short)(insn->data[3] & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0L, subdev_channel));

		/*  Write the Counter Control Register */
		if (insn->data[4] != 0) {
			value = (short)(insn->data[4] & 0xFFFF);
			outw(value, ADDR_CHAN_REG(REG_C0C, subdev_channel));
		}
		break;

	case INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR:
		/*
		   data[0]: Application Type
		   data[1]: Counter Mode Register Value
		   data[2]: Pre-load Register 0 Value
		   data[3]: Pre-load Register 1 Value
		   data[4]: Conter Control Register
		 */
		printk("s526: GPCT_INSN_CONFIG: Configuring PTG\n");
		devpriv->s526_gpct_config[subdev_channel].app =
		    PulseTrainGeneration;

		/*  Set Counter Mode Register */
		cmReg.value = (short)(insn->data[1] & 0xFFFF);
		cmReg.reg.preloadRegSel = 0;	/*  PR0 */
		outw(cmReg.value, ADDR_CHAN_REG(REG_C0M, subdev_channel));

		/*  Load the pre-load register 0 high word */
		value = (short)((insn->data[2] >> 16) & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0H, subdev_channel));

		/*  Load the pre-load register 0 low word */
		value = (short)(insn->data[2] & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0L, subdev_channel));

		/*  Set Counter Mode Register */
		cmReg.value = (short)(insn->data[1] & 0xFFFF);
		cmReg.reg.preloadRegSel = 1;	/*  PR1 */
		outw(cmReg.value, ADDR_CHAN_REG(REG_C0M, subdev_channel));

		/*  Load the pre-load register 1 high word */
		value = (short)((insn->data[3] >> 16) & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0H, subdev_channel));

		/*  Load the pre-load register 1 low word */
		value = (short)(insn->data[3] & 0xFFFF);
		outw(value, ADDR_CHAN_REG(REG_C0L, subdev_channel));

		/*  Write the Counter Control Register */
		if (insn->data[4] != 0) {
			value = (short)(insn->data[4] & 0xFFFF);
			outw(value, ADDR_CHAN_REG(REG_C0C, subdev_channel));
		}
		break;

	default:
		printk("s526: unsupported GPCT_insn_config\n");
		return -EINVAL;
		break;
	}

	return insn->n;
}