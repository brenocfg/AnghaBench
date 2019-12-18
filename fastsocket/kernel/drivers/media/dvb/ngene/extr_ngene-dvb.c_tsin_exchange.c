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
typedef  int /*<<< orphan*/  u32 ;
struct ngene_channel {scalar_t__ users; int /*<<< orphan*/  demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

void *tsin_exchange(void *priv, void *buf, u32 len, u32 clock, u32 flags)
{
	struct ngene_channel *chan = priv;


	if (chan->users > 0)
		dvb_dmx_swfilter(&chan->demux, buf, len);
	return NULL;
}