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
struct videobuf_queue {struct cx8802_fh* priv_data; } ;
struct cx8802_fh {TYPE_1__* dev; } ;
struct TYPE_2__ {int ts_packet_size; unsigned int ts_packet_count; } ;

/* Variables and functions */
 unsigned int mpegbufs ; 

__attribute__((used)) static int bb_buf_setup(struct videobuf_queue *q,
			unsigned int *count, unsigned int *size)
{
	struct cx8802_fh *fh = q->priv_data;

	fh->dev->ts_packet_size  = 188 * 4; /* was: 512 */
	fh->dev->ts_packet_count = mpegbufs; /* was: 100 */

	*size = fh->dev->ts_packet_size * fh->dev->ts_packet_count;
	*count = fh->dev->ts_packet_count;
	return 0;
}