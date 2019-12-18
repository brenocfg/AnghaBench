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
struct saa7134_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7135_DSP_RWCLEAR ; 
 int /*<<< orphan*/  SAA7135_DSP_RWCLEAR_RERR ; 
 int /*<<< orphan*/  SAA7135_DSP_RWSTATE ; 
 int SAA7135_DSP_RWSTATE_ERR ; 
 int /*<<< orphan*/  d2printk (char*,int /*<<< orphan*/ ) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int saa_dsp_reset_error_bit(struct saa7134_dev *dev)
{
	int state = saa_readb(SAA7135_DSP_RWSTATE);
	if (unlikely(state & SAA7135_DSP_RWSTATE_ERR)) {
		d2printk("%s: resetting error bit\n", dev->name);
		saa_writeb(SAA7135_DSP_RWCLEAR, SAA7135_DSP_RWCLEAR_RERR);
	}
	return 0;
}