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
typedef  int u8 ;
struct ttusb_dec {int /*<<< orphan*/  pva_stream_count; } ;
struct dvb_demux_feed {TYPE_1__* demux; } ;
typedef  int /*<<< orphan*/  b0 ;
struct TYPE_2__ {struct ttusb_dec* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttusb_dec_send_command (struct ttusb_dec*,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttusb_dec_stop_iso_xfer (struct ttusb_dec*) ; 

__attribute__((used)) static int ttusb_dec_stop_ts_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct ttusb_dec *dec = dvbdmxfeed->demux->priv;
	u8 b0[] = { 0x00 };

	ttusb_dec_send_command(dec, 0x81, sizeof(b0), b0, NULL, NULL);

	dec->pva_stream_count--;

	ttusb_dec_stop_iso_xfer(dec);

	return 0;
}