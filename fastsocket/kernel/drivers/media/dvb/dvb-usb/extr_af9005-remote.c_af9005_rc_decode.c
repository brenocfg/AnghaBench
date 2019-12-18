#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dvb_usb_device {scalar_t__ last_event; } ;
struct TYPE_4__ {int event; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_KEY_REPEAT ; 
 int /*<<< orphan*/  deb_decode (char*,...) ; 
 int rc5_custom (TYPE_1__*) ; 
 int rc5_data (TYPE_1__*) ; 
 TYPE_1__* rc_map_af9005_table ; 
 int rc_map_af9005_table_size ; 
 scalar_t__* repeatable_keys ; 

int af9005_rc_decode(struct dvb_usb_device *d, u8 * data, int len, u32 * event,
		     int *state)
{
	u16 mark, space;
	u32 result;
	u8 cust, dat, invdat;
	int i;

	if (len >= 6) {
		mark = (u16) (data[0] << 8) + data[1];
		space = (u16) (data[2] << 8) + data[3];
		if (space * 3 < mark) {
			for (i = 0; i < ARRAY_SIZE(repeatable_keys); i++) {
				if (d->last_event == repeatable_keys[i]) {
					*state = REMOTE_KEY_REPEAT;
					*event = d->last_event;
					deb_decode("repeat key, event %x\n",
						   *event);
					return 0;
				}
			}
			deb_decode("repeated key ignored (non repeatable)\n");
			return 0;
		} else if (len >= 33 * 4) {	/*32 bits + start code */
			result = 0;
			for (i = 4; i < 4 + 32 * 4; i += 4) {
				result <<= 1;
				mark = (u16) (data[i] << 8) + data[i + 1];
				mark >>= 1;
				space = (u16) (data[i + 2] << 8) + data[i + 3];
				space >>= 1;
				if (mark * 2 > space)
					result += 1;
			}
			deb_decode("key pressed, raw value %x\n", result);
			if ((result & 0xff000000) != 0xfe000000) {
				deb_decode
				    ("doesn't start with 0xfe, ignored\n");
				return 0;
			}
			cust = (result >> 16) & 0xff;
			dat = (result >> 8) & 0xff;
			invdat = (~result) & 0xff;
			if (dat != invdat) {
				deb_decode("code != inverted code\n");
				return 0;
			}
			for (i = 0; i < rc_map_af9005_table_size; i++) {
				if (rc5_custom(&rc_map_af9005_table[i]) == cust
				    && rc5_data(&rc_map_af9005_table[i]) == dat) {
					*event = rc_map_af9005_table[i].event;
					*state = REMOTE_KEY_PRESSED;
					deb_decode
					    ("key pressed, event %x\n", *event);
					return 0;
				}
			}
			deb_decode("not found in table\n");
		}
	}
	return 0;
}