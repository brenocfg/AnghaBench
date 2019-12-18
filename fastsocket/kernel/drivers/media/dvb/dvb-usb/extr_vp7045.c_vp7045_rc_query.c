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
 int /*<<< orphan*/  RC_VAL_READ ; 
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb_rc (char*,int,int) ; 
 int rc5_data (TYPE_1__*) ; 
 TYPE_1__* rc_map_vp7045_table ; 
 int /*<<< orphan*/  vp7045_usb_op (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int vp7045_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	u8 key;
	int i;
	vp7045_usb_op(d,RC_VAL_READ,NULL,0,&key,1,20);

	deb_rc("remote query key: %x %d\n",key,key);

	if (key == 0x44) {
		*state = REMOTE_NO_KEY_PRESSED;
		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(rc_map_vp7045_table); i++)
		if (rc5_data(&rc_map_vp7045_table[i]) == key) {
			*state = REMOTE_KEY_PRESSED;
			*event = rc_map_vp7045_table[i].event;
			break;
		}
	return 0;
}