#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pp_cam_entry {TYPE_2__* port; } ;
struct TYPE_4__ {scalar_t__ mode; } ;
struct TYPE_5__ {TYPE_1__ ieee1284; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  EndTransferMode (struct pp_cam_entry*) ; 
 scalar_t__ IEEE1284_MODE_NIBBLE ; 
 scalar_t__ ReverseSetup (struct pp_cam_entry*,int /*<<< orphan*/ ) ; 
 size_t cpia_read_nibble (TYPE_2__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t parport_read (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int ReadPacket(struct pp_cam_entry *cam, u8 *packet, size_t size)
{
	int retval=0;

	if (packet == NULL) {
		return -EINVAL;
	}
	if (ReverseSetup(cam, 0)) {
		return -EIO;
	}

	/* support for CPiA variant nibble reads */
	if(cam->port->ieee1284.mode == IEEE1284_MODE_NIBBLE) {
		if(cpia_read_nibble(cam->port, packet, size, 0) != size)
			retval = -EIO;
	} else {
		if(parport_read(cam->port, packet, size) != size)
			retval = -EIO;
	}
	EndTransferMode(cam);
	return retval;
}