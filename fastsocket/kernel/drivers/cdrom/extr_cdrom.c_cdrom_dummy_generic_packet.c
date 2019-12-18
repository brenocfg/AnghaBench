#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct packet_command {int stat; TYPE_1__* sense; } ;
struct cdrom_device_info {int dummy; } ;
struct TYPE_2__ {int sense_key; int asc; int ascq; } ;

/* Variables and functions */
 int EIO ; 

__attribute__((used)) static int cdrom_dummy_generic_packet(struct cdrom_device_info *cdi,
				      struct packet_command *cgc)
{
	if (cgc->sense) {
		cgc->sense->sense_key = 0x05;
		cgc->sense->asc = 0x20;
		cgc->sense->ascq = 0x00;
	}

	cgc->stat = -EIO;
	return -EIO;
}