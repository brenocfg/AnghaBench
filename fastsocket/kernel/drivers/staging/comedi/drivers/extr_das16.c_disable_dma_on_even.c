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
struct TYPE_2__ {int /*<<< orphan*/  dma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int get_dma_residue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int disable_dma_on_even(struct comedi_device *dev)
{
	int residue;
	int i;
	static const int disable_limit = 100;
	static const int enable_timeout = 100;
	disable_dma(devpriv->dma_chan);
	residue = get_dma_residue(devpriv->dma_chan);
	for (i = 0; i < disable_limit && (residue % 2); ++i) {
		int j;
		enable_dma(devpriv->dma_chan);
		for (j = 0; j < enable_timeout; ++j) {
			int new_residue;
			udelay(2);
			new_residue = get_dma_residue(devpriv->dma_chan);
			if (new_residue != residue)
				break;
		}
		disable_dma(devpriv->dma_chan);
		residue = get_dma_residue(devpriv->dma_chan);
	}
	if (i == disable_limit) {
		comedi_error(dev,
			     "failed to get an even dma transfer, could be trouble.");
	}
	return residue;
}