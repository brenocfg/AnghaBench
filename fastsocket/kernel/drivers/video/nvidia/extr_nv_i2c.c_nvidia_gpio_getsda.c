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
struct nvidia_par {int dummy; } ;
struct nvidia_i2c_chan {int /*<<< orphan*/  ddc_base; struct nvidia_par* par; } ;

/* Variables and functions */
 int NVReadCrtc (struct nvidia_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvidia_gpio_getsda(void *data)
{
	struct nvidia_i2c_chan *chan = data;
	struct nvidia_par *par = chan->par;
	u32 val = 0;

	if (NVReadCrtc(par, chan->ddc_base) & 0x08)
		val = 1;

	return val;
}