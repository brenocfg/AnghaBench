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
typedef  int u32 ;
struct talitos_private {int num_channels; scalar_t__ reg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ TALITOS_CCCR (int) ; 
 int TALITOS_CCCR_CONT ; 
 scalar_t__ TALITOS_CCCR_LO (int) ; 
 scalar_t__ TALITOS_CCPSR (int) ; 
 scalar_t__ TALITOS_CCPSR_LO (int) ; 
 int TALITOS_CCPSR_LO_DOF ; 
 int TALITOS_CCPSR_LO_EU ; 
 int TALITOS_CCPSR_LO_FPZ ; 
 int TALITOS_CCPSR_LO_GB ; 
 int TALITOS_CCPSR_LO_GRL ; 
 int TALITOS_CCPSR_LO_IDH ; 
 int TALITOS_CCPSR_LO_IEU ; 
 int TALITOS_CCPSR_LO_MDTE ; 
 int TALITOS_CCPSR_LO_SB ; 
 int TALITOS_CCPSR_LO_SGDLZ ; 
 int TALITOS_CCPSR_LO_SOF ; 
 int TALITOS_CCPSR_LO_SRL ; 
 int TALITOS_ISR_CHERR ; 
 unsigned int TALITOS_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  current_desc (struct device*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_channel (struct device*,int,int,int) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  init_device (struct device*) ; 
 int /*<<< orphan*/  report_eu_error (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_channel (struct device*,int) ; 
 int /*<<< orphan*/  setbits32 (scalar_t__,int) ; 

__attribute__((used)) static void talitos_error(unsigned long data, u32 isr, u32 isr_lo)
{
	struct device *dev = (struct device *)data;
	struct talitos_private *priv = dev_get_drvdata(dev);
	unsigned int timeout = TALITOS_TIMEOUT;
	int ch, error, reset_dev = 0, reset_ch = 0;
	u32 v, v_lo;

	for (ch = 0; ch < priv->num_channels; ch++) {
		/* skip channels without errors */
		if (!(isr & (1 << (ch * 2 + 1))))
			continue;

		error = -EINVAL;

		v = in_be32(priv->reg + TALITOS_CCPSR(ch));
		v_lo = in_be32(priv->reg + TALITOS_CCPSR_LO(ch));

		if (v_lo & TALITOS_CCPSR_LO_DOF) {
			dev_err(dev, "double fetch fifo overflow error\n");
			error = -EAGAIN;
			reset_ch = 1;
		}
		if (v_lo & TALITOS_CCPSR_LO_SOF) {
			/* h/w dropped descriptor */
			dev_err(dev, "single fetch fifo overflow error\n");
			error = -EAGAIN;
		}
		if (v_lo & TALITOS_CCPSR_LO_MDTE)
			dev_err(dev, "master data transfer error\n");
		if (v_lo & TALITOS_CCPSR_LO_SGDLZ)
			dev_err(dev, "s/g data length zero error\n");
		if (v_lo & TALITOS_CCPSR_LO_FPZ)
			dev_err(dev, "fetch pointer zero error\n");
		if (v_lo & TALITOS_CCPSR_LO_IDH)
			dev_err(dev, "illegal descriptor header error\n");
		if (v_lo & TALITOS_CCPSR_LO_IEU)
			dev_err(dev, "invalid execution unit error\n");
		if (v_lo & TALITOS_CCPSR_LO_EU)
			report_eu_error(dev, ch, current_desc(dev, ch));
		if (v_lo & TALITOS_CCPSR_LO_GB)
			dev_err(dev, "gather boundary error\n");
		if (v_lo & TALITOS_CCPSR_LO_GRL)
			dev_err(dev, "gather return/length error\n");
		if (v_lo & TALITOS_CCPSR_LO_SB)
			dev_err(dev, "scatter boundary error\n");
		if (v_lo & TALITOS_CCPSR_LO_SRL)
			dev_err(dev, "scatter return/length error\n");

		flush_channel(dev, ch, error, reset_ch);

		if (reset_ch) {
			reset_channel(dev, ch);
		} else {
			setbits32(priv->reg + TALITOS_CCCR(ch),
				  TALITOS_CCCR_CONT);
			setbits32(priv->reg + TALITOS_CCCR_LO(ch), 0);
			while ((in_be32(priv->reg + TALITOS_CCCR(ch)) &
			       TALITOS_CCCR_CONT) && --timeout)
				cpu_relax();
			if (timeout == 0) {
				dev_err(dev, "failed to restart channel %d\n",
					ch);
				reset_dev = 1;
			}
		}
	}
	if (reset_dev || isr & ~TALITOS_ISR_CHERR || isr_lo) {
		dev_err(dev, "done overflow, internal time out, or rngu error: "
		        "ISR 0x%08x_%08x\n", isr, isr_lo);

		/* purge request queues */
		for (ch = 0; ch < priv->num_channels; ch++)
			flush_channel(dev, ch, -EIO, 1);

		/* reset and reinitialize the device */
		init_device(dev);
	}
}