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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct m920x_state {int rep_count; } ;
struct TYPE_3__ {int rc_key_map_size; TYPE_2__* rc_key_map; } ;
struct dvb_usb_device {TYPE_1__ props; int /*<<< orphan*/  udev; struct m920x_state* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  M9206_CORE ; 
 int /*<<< orphan*/  M9206_RC_KEY ; 
 int /*<<< orphan*/  M9206_RC_STATE ; 
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_KEY_REPEAT ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb (char*,int) ; 
 int m920x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int) ; 
 int rc5_data (TYPE_2__*) ; 

__attribute__((used)) static int m920x_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	struct m920x_state *m = d->priv;
	int i, ret = 0;
	u8 rc_state[2];

	if ((ret = m920x_read(d->udev, M9206_CORE, 0x0, M9206_RC_STATE, rc_state, 1)) != 0)
		goto unlock;

	if ((ret = m920x_read(d->udev, M9206_CORE, 0x0, M9206_RC_KEY, rc_state + 1, 1)) != 0)
		goto unlock;

	for (i = 0; i < d->props.rc_key_map_size; i++)
		if (rc5_data(&d->props.rc_key_map[i]) == rc_state[1]) {
			*event = d->props.rc_key_map[i].event;

			switch(rc_state[0]) {
			case 0x80:
				*state = REMOTE_NO_KEY_PRESSED;
				goto unlock;

			case 0x88: /* framing error or "invalid code" */
			case 0x99:
			case 0xc0:
			case 0xd8:
				*state = REMOTE_NO_KEY_PRESSED;
				m->rep_count = 0;
				goto unlock;

			case 0x93:
			case 0x92:
			case 0x83: /* pinnacle PCTV310e */
			case 0x82:
				m->rep_count = 0;
				*state = REMOTE_KEY_PRESSED;
				goto unlock;

			case 0x91:
			case 0x81: /* pinnacle PCTV310e */
				/* prevent immediate auto-repeat */
				if (++m->rep_count > 2)
					*state = REMOTE_KEY_REPEAT;
				else
					*state = REMOTE_NO_KEY_PRESSED;
				goto unlock;

			default:
				deb("Unexpected rc state %02x\n", rc_state[0]);
				*state = REMOTE_NO_KEY_PRESSED;
				goto unlock;
			}
		}

	if (rc_state[1] != 0)
		deb("Unknown rc key %02x\n", rc_state[1]);

	*state = REMOTE_NO_KEY_PRESSED;

 unlock:

	return ret;
}