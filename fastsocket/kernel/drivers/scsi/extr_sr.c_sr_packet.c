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
struct packet_command {scalar_t__ timeout; int stat; } ;
struct cdrom_device_info {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ IOCTL_TIMEOUT ; 
 int /*<<< orphan*/  sr_do_ioctl (int /*<<< orphan*/ ,struct packet_command*) ; 

__attribute__((used)) static int sr_packet(struct cdrom_device_info *cdi,
		struct packet_command *cgc)
{
	if (cgc->timeout <= 0)
		cgc->timeout = IOCTL_TIMEOUT;

	sr_do_ioctl(cdi->handle, cgc);

	return cgc->stat;
}