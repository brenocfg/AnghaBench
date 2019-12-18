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
 int /*<<< orphan*/  RtdClearCGT (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdEnableCGT (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdWriteCGLatch (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtdWriteCGTable (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtdConvertChanGain (struct comedi_device*,unsigned int,int) ; 

__attribute__((used)) static void rtd_load_channelgain_list(struct comedi_device *dev,
				      unsigned int n_chan, unsigned int *list)
{
	if (n_chan > 1) {	/* setup channel gain table */
		int ii;
		RtdClearCGT(dev);
		RtdEnableCGT(dev, 1);	/* enable table */
		for (ii = 0; ii < n_chan; ii++) {
			RtdWriteCGTable(dev, rtdConvertChanGain(dev, list[ii],
								ii));
		}
	} else {		/* just use the channel gain latch */
		RtdEnableCGT(dev, 0);	/* disable table, enable latch */
		RtdWriteCGLatch(dev, rtdConvertChanGain(dev, list[0], 0));
	}
}