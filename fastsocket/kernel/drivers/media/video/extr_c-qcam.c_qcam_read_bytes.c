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
struct qcam_device {int /*<<< orphan*/  pport; scalar_t__ bidirectional; } ;

/* Variables and functions */
 scalar_t__ force_rgb ; 
 int parport_read_data (int /*<<< orphan*/ ) ; 
 int parport_read_status (int /*<<< orphan*/ ) ; 
 scalar_t__ qcam_await_ready1 (struct qcam_device*,int) ; 
 scalar_t__ qcam_await_ready2 (struct qcam_device*,int) ; 
 int /*<<< orphan*/  qcam_set_ack (struct qcam_device*,int) ; 

__attribute__((used)) static unsigned int qcam_read_bytes(struct qcam_device *q, unsigned char *buf, unsigned int nbytes)
{
	unsigned int bytes = 0;

	qcam_set_ack(q, 0);
	if (q->bidirectional)
	{
		/* It's a bidirectional port */
		while (bytes < nbytes)
		{
			unsigned int lo1, hi1, lo2, hi2;
			unsigned char r, g, b;

			if (qcam_await_ready2(q, 1)) return bytes;
			lo1 = parport_read_data(q->pport) >> 1;
			hi1 = ((parport_read_status(q->pport) >> 3) & 0x1f) ^ 0x10;
			qcam_set_ack(q, 1);
			if (qcam_await_ready2(q, 0)) return bytes;
			lo2 = parport_read_data(q->pport) >> 1;
			hi2 = ((parport_read_status(q->pport) >> 3) & 0x1f) ^ 0x10;
			qcam_set_ack(q, 0);
			r = (lo1 | ((hi1 & 1)<<7));
			g = ((hi1 & 0x1e)<<3) | ((hi2 & 0x1e)>>1);
			b = (lo2 | ((hi2 & 1)<<7));
			if (force_rgb) {
				buf[bytes++] = r;
				buf[bytes++] = g;
				buf[bytes++] = b;
			} else {
				buf[bytes++] = b;
				buf[bytes++] = g;
				buf[bytes++] = r;
			}
		}
	}
	else
	{
		/* It's a unidirectional port */
		int i = 0, n = bytes;
		unsigned char rgb[3];

		while (bytes < nbytes)
		{
			unsigned int hi, lo;

			if (qcam_await_ready1(q, 1)) return bytes;
			hi = (parport_read_status(q->pport) & 0xf0);
			qcam_set_ack(q, 1);
			if (qcam_await_ready1(q, 0)) return bytes;
			lo = (parport_read_status(q->pport) & 0xf0);
			qcam_set_ack(q, 0);
			/* flip some bits */
			rgb[(i = bytes++ % 3)] = (hi | (lo >> 4)) ^ 0x88;
			if (i >= 2) {
get_fragment:
				if (force_rgb) {
					buf[n++] = rgb[0];
					buf[n++] = rgb[1];
					buf[n++] = rgb[2];
				} else {
					buf[n++] = rgb[2];
					buf[n++] = rgb[1];
					buf[n++] = rgb[0];
				}
			}
		}
		if (i) {
			i = 0;
			goto get_fragment;
		}
	}
	return bytes;
}