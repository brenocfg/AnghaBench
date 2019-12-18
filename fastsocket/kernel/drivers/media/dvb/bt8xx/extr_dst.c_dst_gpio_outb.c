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
struct TYPE_4__ {int mask; int highvals; } ;
struct TYPE_3__ {int mask; int enable; } ;
union dst_gpio_packet {TYPE_2__ outp; TYPE_1__ enb; } ;
typedef  int u32 ;
struct dst_state {int /*<<< orphan*/  bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_IG_ENABLE ; 
 int /*<<< orphan*/  DST_IG_WRITE ; 
 int /*<<< orphan*/  DST_INFO ; 
 int EREMOTEIO ; 
 int bt878_device_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union dst_gpio_packet*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_gpio_outb(struct dst_state *state, u32 mask, u32 enbb,
			 u32 outhigh, int delay)
{
	union dst_gpio_packet enb;
	union dst_gpio_packet bits;
	int err;

	enb.enb.mask = mask;
	enb.enb.enable = enbb;

	dprintk(verbose, DST_INFO, 1, "mask=[%04x], enbb=[%04x], outhigh=[%04x]", mask, enbb, outhigh);
	if ((err = bt878_device_control(state->bt, DST_IG_ENABLE, &enb)) < 0) {
		dprintk(verbose, DST_INFO, 1, "dst_gpio_enb error (err == %i, mask == %02x, enb == %02x)", err, mask, enbb);
		return -EREMOTEIO;
	}
	udelay(1000);
	/* because complete disabling means no output, no need to do output packet */
	if (enbb == 0)
		return 0;
	if (delay)
		msleep(10);
	bits.outp.mask = enbb;
	bits.outp.highvals = outhigh;
	if ((err = bt878_device_control(state->bt, DST_IG_WRITE, &bits)) < 0) {
		dprintk(verbose, DST_INFO, 1, "dst_gpio_outb error (err == %i, enbb == %02x, outhigh == %02x)", err, enbb, outhigh);
		return -EREMOTEIO;
	}

	return 0;
}