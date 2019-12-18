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
struct urb {int transfer_buffer_length; scalar_t__ transfer_buffer; } ;

/* Variables and functions */

__attribute__((used)) static void change_volume(struct urb *urb_out, int volume[],
			  int bytes_per_frame)
{
	int chn = 0;

	if (volume[0] == 256 && volume[1] == 256)
		return;  /* maximum volume - no change */

	if (bytes_per_frame == 4) {
		short *p, *buf_end;
		p = (short *)urb_out->transfer_buffer;
		buf_end = p + urb_out->transfer_buffer_length / sizeof(*p);

		for (; p < buf_end; ++p) {
			*p = (*p * volume[chn & 1]) >> 8;
			++chn;
		}
	} else if (bytes_per_frame == 6) {
		unsigned char *p, *buf_end;
		p = (unsigned char *)urb_out->transfer_buffer;
		buf_end = p + urb_out->transfer_buffer_length;

		for (; p < buf_end; p += 3) {
			int val;
			val = p[0] + (p[1] << 8) + ((signed char)p[2] << 16);
			val = (val * volume[chn & 1]) >> 8;
			p[0] = val;
			p[1] = val >> 8;
			p[2] = val >> 16;
			++chn;
		}
	}
}