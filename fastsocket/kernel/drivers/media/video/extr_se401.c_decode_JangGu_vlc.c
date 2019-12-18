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
struct usb_se401 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_JangGu_integrate (struct usb_se401*,int) ; 

__attribute__((used)) static inline void decode_JangGu_vlc(struct usb_se401 *se401,
			unsigned char *data, int bit_exp, int packetlength)
{
	int pos = 0;
	int vlc_cod = 0;
	int vlc_size = 0;
	int vlc_data = 0;
	int bit_cur;
	int bit;
	data += 4;
	while (pos < packetlength) {
		bit_cur = 8;
		while (bit_cur && bit_exp) {
			bit = ((*data) >> (bit_cur-1))&1;
			if (!vlc_cod) {
				if (bit) {
					vlc_size++;
				} else {
					if (!vlc_size)
						decode_JangGu_integrate(se401, 0);
					else {
						vlc_cod = 2;
						vlc_data = 0;
					}
				}
			} else {
				if (vlc_cod == 2) {
					if (!bit)
						vlc_data =  -(1 << vlc_size) + 1;
					vlc_cod--;
				}
				vlc_size--;
				vlc_data += bit << vlc_size;
				if (!vlc_size) {
					decode_JangGu_integrate(se401, vlc_data);
					vlc_cod = 0;
				}
			}
			bit_cur--;
			bit_exp--;
		}
		pos++;
		data++;
	}
}