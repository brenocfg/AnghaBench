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
struct ttusb_dec {int /*<<< orphan*/  filter_stream_count; int /*<<< orphan*/  filter_info_list_lock; } ;
struct filter_info {int stream_id; int /*<<< orphan*/  filter_info_list; } ;
struct dvb_demux_feed {scalar_t__ priv; TYPE_1__* demux; } ;
typedef  int /*<<< orphan*/  b0 ;
struct TYPE_2__ {struct ttusb_dec* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct filter_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ttusb_dec_send_command (struct ttusb_dec*,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttusb_dec_stop_iso_xfer (struct ttusb_dec*) ; 

__attribute__((used)) static int ttusb_dec_stop_sec_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct ttusb_dec *dec = dvbdmxfeed->demux->priv;
	u8 b0[] = { 0x00, 0x00 };
	struct filter_info *finfo = (struct filter_info *)dvbdmxfeed->priv;
	unsigned long flags;

	b0[1] = finfo->stream_id;
	spin_lock_irqsave(&dec->filter_info_list_lock, flags);
	list_del(&finfo->filter_info_list);
	spin_unlock_irqrestore(&dec->filter_info_list_lock, flags);
	kfree(finfo);
	ttusb_dec_send_command(dec, 0x62, sizeof(b0), b0, NULL, NULL);

	dec->filter_stream_count--;

	ttusb_dec_stop_iso_xfer(dec);

	return 0;
}