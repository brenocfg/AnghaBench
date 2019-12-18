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
struct nvidia_i2c_chan {scalar_t__ ddc_base; struct nvidia_par* par; } ;

/* Variables and functions */
 int NVReadCrtc (struct nvidia_par*,scalar_t__) ; 
 int /*<<< orphan*/  NVWriteCrtc (struct nvidia_par*,scalar_t__,int) ; 

__attribute__((used)) static void nvidia_gpio_setsda(void *data, int state)
{
	struct nvidia_i2c_chan *chan = data;
	struct nvidia_par *par = chan->par;
	u32 val;

	val = NVReadCrtc(par, chan->ddc_base + 1) & 0xf0;

	if (state)
		val |= 0x10;
	else
		val &= ~0x10;

	NVWriteCrtc(par, chan->ddc_base + 1, val | 0x01);
}