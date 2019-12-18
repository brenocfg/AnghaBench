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
typedef  int /*<<< orphan*/  u8 ;
struct pp_cam_entry {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  EndTransferMode (struct pp_cam_entry*) ; 
 scalar_t__ ForwardSetup (struct pp_cam_entry*) ; 
 int parport_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int WritePacket(struct pp_cam_entry *cam, const u8 *packet, size_t size)
{
	int retval=0;
	int size_written;

	if (packet == NULL) {
		return -EINVAL;
	}
	if (ForwardSetup(cam)) {
		DBG("Write failed in setup\n");
		return -EIO;
	}
	size_written = parport_write(cam->port, packet, size);
	if(size_written != size) {
		DBG("Write failed, wrote %d/%d\n", size_written, size);
		retval = -EIO;
	}
	EndTransferMode(cam);
	return retval;
}