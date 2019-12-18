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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CSCFG_PORT_MODE ; 
 unsigned int CSCFG_SELF_CAL_OFFSET ; 
 unsigned int CSCFG_SELF_CAL_OFFSET_GAIN ; 
 unsigned int CSCFG_WORD_RATE_2180_CYCLES ; 
 int /*<<< orphan*/  CSCMD_CONFIG_REGISTER ; 
 int /*<<< orphan*/  CSCMD_GAIN_REGISTER ; 
 int /*<<< orphan*/  CSCMD_OFFSET_REGISTER ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  cs5529_config_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5529_config_write (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5529_do_conversion (struct comedi_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ cs5529_wait_for_idle (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_cs5529(struct comedi_device *dev)
{
	unsigned int config_bits =
	    CSCFG_PORT_MODE | CSCFG_WORD_RATE_2180_CYCLES;

#if 1
	/* do self-calibration */
	cs5529_config_write(dev, config_bits | CSCFG_SELF_CAL_OFFSET_GAIN,
			    CSCMD_CONFIG_REGISTER);
	/* need to force a conversion for calibration to run */
	cs5529_do_conversion(dev, NULL);
#else
	/* force gain calibration to 1 */
	cs5529_config_write(dev, 0x400000, CSCMD_GAIN_REGISTER);
	cs5529_config_write(dev, config_bits | CSCFG_SELF_CAL_OFFSET,
			    CSCMD_CONFIG_REGISTER);
	if (cs5529_wait_for_idle(dev))
		comedi_error(dev, "timeout or signal in init_cs5529()\n");
#endif
#ifdef NI_CS5529_DEBUG
	printk("config: 0x%x\n", cs5529_config_read(dev,
						    CSCMD_CONFIG_REGISTER));
	printk("gain: 0x%x\n", cs5529_config_read(dev, CSCMD_GAIN_REGISTER));
	printk("offset: 0x%x\n", cs5529_config_read(dev,
						    CSCMD_OFFSET_REGISTER));
#endif
	return 0;
}