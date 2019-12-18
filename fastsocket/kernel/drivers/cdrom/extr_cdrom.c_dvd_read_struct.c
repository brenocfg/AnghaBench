#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct packet_command {int dummy; } ;
struct cdrom_device_info {int dummy; } ;
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ dvd_struct ;

/* Variables and functions */
 int /*<<< orphan*/  CD_WARNING ; 
#define  DVD_STRUCT_BCA 132 
#define  DVD_STRUCT_COPYRIGHT 131 
#define  DVD_STRUCT_DISCKEY 130 
#define  DVD_STRUCT_MANUFACT 129 
#define  DVD_STRUCT_PHYSICAL 128 
 int EINVAL ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*,int) ; 
 int dvd_read_bca (struct cdrom_device_info*,TYPE_1__*,struct packet_command*) ; 
 int dvd_read_copyright (struct cdrom_device_info*,TYPE_1__*,struct packet_command*) ; 
 int dvd_read_disckey (struct cdrom_device_info*,TYPE_1__*,struct packet_command*) ; 
 int dvd_read_manufact (struct cdrom_device_info*,TYPE_1__*,struct packet_command*) ; 
 int dvd_read_physical (struct cdrom_device_info*,TYPE_1__*,struct packet_command*) ; 

__attribute__((used)) static int dvd_read_struct(struct cdrom_device_info *cdi, dvd_struct *s,
				struct packet_command *cgc)
{
	switch (s->type) {
	case DVD_STRUCT_PHYSICAL:
		return dvd_read_physical(cdi, s, cgc);

	case DVD_STRUCT_COPYRIGHT:
		return dvd_read_copyright(cdi, s, cgc);

	case DVD_STRUCT_DISCKEY:
		return dvd_read_disckey(cdi, s, cgc);

	case DVD_STRUCT_BCA:
		return dvd_read_bca(cdi, s, cgc);

	case DVD_STRUCT_MANUFACT:
		return dvd_read_manufact(cdi, s, cgc);
		
	default:
		cdinfo(CD_WARNING, ": Invalid DVD structure read requested (%d)\n",
					s->type);
		return -EINVAL;
	}
}