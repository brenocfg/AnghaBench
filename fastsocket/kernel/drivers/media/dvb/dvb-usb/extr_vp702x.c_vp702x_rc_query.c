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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_usb_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  READ_REMOTE_REQ ; 
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb_rc (char*,int,int) ; 
 int rc5_custom (TYPE_1__*) ; 
 TYPE_1__* rc_map_vp702x_table ; 
 int /*<<< orphan*/  vp702x_usb_in_op (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int vp702x_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	u8 key[10];
	int i;

/* remove the following return to enabled remote querying */
	return 0;

	vp702x_usb_in_op(d,READ_REMOTE_REQ,0,0,key,10);

	deb_rc("remote query key: %x %d\n",key[1],key[1]);

	if (key[1] == 0x44) {
		*state = REMOTE_NO_KEY_PRESSED;
		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(rc_map_vp702x_table); i++)
		if (rc5_custom(&rc_map_vp702x_table[i]) == key[1]) {
			*state = REMOTE_KEY_PRESSED;
			*event = rc_map_vp702x_table[i].event;
			break;
		}
	return 0;
}