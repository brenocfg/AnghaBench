#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {int ptt; scalar_t__ numbits; scalar_t__ bitstream; scalar_t__ bitbuf; int /*<<< orphan*/  numflags; scalar_t__ tx_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_delay; } ;
struct hdlcdrv_state {int /*<<< orphan*/  ptt_keyed; TYPE_2__ hdlctx; TYPE_1__ ch_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdlcdrv_transmitter (struct net_device*,struct hdlcdrv_state*) ; 
 int /*<<< orphan*/  tenms_to_2flags (struct hdlcdrv_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_tx(struct net_device *dev, struct hdlcdrv_state *s)
{
	s->hdlctx.tx_state = 0;
	s->hdlctx.numflags = tenms_to_2flags(s, s->ch_params.tx_delay);
	s->hdlctx.bitbuf = s->hdlctx.bitstream = s->hdlctx.numbits = 0;
	hdlcdrv_transmitter(dev, s);
	s->hdlctx.ptt = 1;
	s->ptt_keyed++;
}