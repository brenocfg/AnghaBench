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
struct pp_cam_entry {TYPE_2__* port; } ;
struct TYPE_3__ {int mode; } ;
struct TYPE_4__ {int modes; TYPE_1__ ieee1284; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int ECP_TRANSFER ; 
 int IEEE1284_EXT_LINK ; 
 int IEEE1284_MODE_ECP ; 
 int IEEE1284_MODE_NIBBLE ; 
 int NIBBLE_TRANSFER ; 
 int PARPORT_MODE_ECP ; 
 int PARPORT_MODE_TRISTATE ; 
 int UPLOAD_FLAG ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  parport_negotiate (TYPE_2__*,int) ; 

__attribute__((used)) static int ReverseSetup(struct pp_cam_entry *cam, int extensibility)
{
	int retry;
	int upload_mode, mode = IEEE1284_MODE_ECP;
	int transfer_mode = ECP_TRANSFER;

	if (!(cam->port->modes & PARPORT_MODE_ECP) &&
	     !(cam->port->modes & PARPORT_MODE_TRISTATE)) {
		mode = IEEE1284_MODE_NIBBLE;
		transfer_mode = NIBBLE_TRANSFER;
	}

	upload_mode = mode;
	if(extensibility) mode = UPLOAD_FLAG|transfer_mode|IEEE1284_EXT_LINK;

	/* the usual camera maximum response time is 10ms, but after
	 * receiving some commands, it needs up to 40ms. */

	for(retry = 0; retry < 4; ++retry) {
		if(!parport_negotiate(cam->port, mode)) {
			break;
		}
		mdelay(10);
	}
	if(retry == 4) {
		if(extensibility)
			DBG("Unable to negotiate upload extensibility mode\n");
		else
			DBG("Unable to negotiate upload mode\n");
		return -1;
	}
	if(extensibility) cam->port->ieee1284.mode = upload_mode;
	return 0;
}