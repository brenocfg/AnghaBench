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
struct hpsb_iso_packet_info {scalar_t__ total_len; } ;
struct hpsb_iso {scalar_t__ type; size_t first_packet; int buf_packets; scalar_t__ n_ready_packets; scalar_t__ bytes_discarded; int /*<<< orphan*/  lock; TYPE_2__* host; int /*<<< orphan*/ * infos; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int (* isoctl ) (struct hpsb_iso*,int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 scalar_t__ HPSB_ISO_RECV ; 
 int /*<<< orphan*/  RECV_RELEASE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct hpsb_iso*,int /*<<< orphan*/ ,unsigned long) ; 
 int stub2 (struct hpsb_iso*,int /*<<< orphan*/ ,unsigned long) ; 

int hpsb_iso_recv_release_packets(struct hpsb_iso *iso, unsigned int n_packets)
{
	unsigned long flags;
	unsigned int i;
	int rv = 0;

	if (iso->type != HPSB_ISO_RECV)
		return -1;

	spin_lock_irqsave(&iso->lock, flags);
	for (i = 0; i < n_packets; i++) {
		rv = iso->host->driver->isoctl(iso, RECV_RELEASE,
					       (unsigned long)&iso->infos[iso->
									  first_packet]);
		if (rv)
			break;

		iso->first_packet = (iso->first_packet + 1) % iso->buf_packets;
		iso->n_ready_packets--;

		/* release memory from packets discarded when queue was full  */
		if (iso->n_ready_packets == 0) {	/* Release only after all prior packets handled */
			if (iso->bytes_discarded != 0) {
				struct hpsb_iso_packet_info inf;
				inf.total_len = iso->bytes_discarded;
				iso->host->driver->isoctl(iso, RECV_RELEASE,
							  (unsigned long)&inf);
				iso->bytes_discarded = 0;
			}
		}
	}
	spin_unlock_irqrestore(&iso->lock, flags);
	return rv;
}