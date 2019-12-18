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
typedef  int u8 ;
struct dvb_demux {int tsbufp; int* tsbuf; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_swfilter_packet (struct dvb_demux*,int const*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dvb_dmx_swfilter(struct dvb_demux *demux, const u8 *buf, size_t count)
{
	int p = 0, i, j;

	spin_lock(&demux->lock);

	if (demux->tsbufp) {
		i = demux->tsbufp;
		j = 188 - i;
		if (count < j) {
			memcpy(&demux->tsbuf[i], buf, count);
			demux->tsbufp += count;
			goto bailout;
		}
		memcpy(&demux->tsbuf[i], buf, j);
		if (demux->tsbuf[0] == 0x47)
			dvb_dmx_swfilter_packet(demux, demux->tsbuf);
		demux->tsbufp = 0;
		p += j;
	}

	while (p < count) {
		if (buf[p] == 0x47) {
			if (count - p >= 188) {
				dvb_dmx_swfilter_packet(demux, &buf[p]);
				p += 188;
			} else {
				i = count - p;
				memcpy(demux->tsbuf, &buf[p], i);
				demux->tsbufp = i;
				goto bailout;
			}
		} else
			p++;
	}

bailout:
	spin_unlock(&demux->lock);
}