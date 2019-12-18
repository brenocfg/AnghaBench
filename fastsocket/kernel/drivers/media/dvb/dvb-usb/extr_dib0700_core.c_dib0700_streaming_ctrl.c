#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct dvb_usb_adapter {int id; TYPE_1__* dev; } ;
struct dib0700_state {int fw_version; int disable_streaming_master_mode; int channel_state; int /*<<< orphan*/  nb_packet_buffer_size; } ;
struct TYPE_3__ {struct dib0700_state* priv; } ;

/* Variables and functions */
 int REQUEST_ENABLE_VIDEO ; 
 int /*<<< orphan*/  deb_info (char*,...) ; 
 int dib0700_ctrl_wr (TYPE_1__*,int*,int) ; 
 int dib0700_set_usb_xfer_len (TYPE_1__*,int /*<<< orphan*/ ) ; 

int dib0700_streaming_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	struct dib0700_state *st = adap->dev->priv;
	u8 b[4];
	int ret;

	if ((onoff != 0) && (st->fw_version >= 0x10201)) {
		/* for firmware later than 1.20.1,
		 * the USB xfer length can be set  */
		ret = dib0700_set_usb_xfer_len(adap->dev,
			st->nb_packet_buffer_size);
		if (ret < 0) {
			deb_info("can not set the USB xfer len\n");
			return ret;
		}
	}

	b[0] = REQUEST_ENABLE_VIDEO;
	b[1] = (onoff << 4) | 0x00; /* this bit gives a kind of command, rather than enabling something or not */

	if (st->disable_streaming_master_mode == 1)
		b[2] = 0x00;
	else
		b[2] = 0x01 << 4; /* Master mode */

	b[3] = 0x00;

	deb_info("modifying (%d) streaming state for %d\n", onoff, adap->id);

	if (onoff)
		st->channel_state |=   1 << adap->id;
	else
		st->channel_state &= ~(1 << adap->id);

	b[2] |= st->channel_state;

	deb_info("data for streaming: %x %x\n", b[1], b[2]);

	return dib0700_ctrl_wr(adap->dev, b, 4);
}