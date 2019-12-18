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
struct TYPE_2__ {int /*<<< orphan*/  irq_interval; int /*<<< orphan*/  speed; int /*<<< orphan*/  channel; int /*<<< orphan*/  buf_packets; int /*<<< orphan*/  data_buf_size; } ;
struct raw1394_iso_status {int overflows; int /*<<< orphan*/  xmit_cycle; int /*<<< orphan*/  n_packets; TYPE_1__ config; } ;
struct hpsb_iso {int /*<<< orphan*/  xmit_cycle; int /*<<< orphan*/  irq_interval; int /*<<< orphan*/  speed; int /*<<< orphan*/  channel; int /*<<< orphan*/  buf_packets; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  skips; int /*<<< orphan*/  overflows; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpsb_iso_n_ready (struct hpsb_iso*) ; 

__attribute__((used)) static void raw1394_iso_fill_status(struct hpsb_iso *iso,
				    struct raw1394_iso_status *stat)
{
	int overflows = atomic_read(&iso->overflows);
	int skips = atomic_read(&iso->skips);

	stat->config.data_buf_size = iso->buf_size;
	stat->config.buf_packets = iso->buf_packets;
	stat->config.channel = iso->channel;
	stat->config.speed = iso->speed;
	stat->config.irq_interval = iso->irq_interval;
	stat->n_packets = hpsb_iso_n_ready(iso);
	stat->overflows = ((skips & 0xFFFF) << 16) | ((overflows & 0xFFFF));
	stat->xmit_cycle = iso->xmit_cycle;
}