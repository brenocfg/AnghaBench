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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_RC_CODE ; 
 int /*<<< orphan*/  deb_info (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dvb_usb_generic_rw (struct dvb_usb_device*,scalar_t__*,int,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_usb_nec_rc_key_to_event (struct dvb_usb_device*,scalar_t__*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int dtt200u_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	u8 key[5],cmd = GET_RC_CODE;
	dvb_usb_generic_rw(d,&cmd,1,key,5,0);
	dvb_usb_nec_rc_key_to_event(d,key,event,state);
	if (key[0] != 0)
		deb_info("key: %x %x %x %x %x\n",key[0],key[1],key[2],key[3],key[4]);
	return 0;
}