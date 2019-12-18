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
typedef  void* u_char ;
struct packet_command {int* cmd; int buflen; } ;
struct cdrom_device_ops {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;
struct cdrom_device_info {struct cdrom_device_ops* ops; } ;
struct TYPE_4__ {int layer_num; void* rmi; void* cpst; } ;
struct TYPE_5__ {int type; TYPE_1__ copyright; } ;
typedef  TYPE_2__ dvd_struct ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int GPCMD_READ_DVD_STRUCTURE ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,void**,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int dvd_read_copyright(struct cdrom_device_info *cdi, dvd_struct *s,
				struct packet_command *cgc)
{
	int ret;
	u_char buf[8];
	struct cdrom_device_ops *cdo = cdi->ops;

	init_cdrom_command(cgc, buf, sizeof(buf), CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[6] = s->copyright.layer_num;
	cgc->cmd[7] = s->type;
	cgc->cmd[8] = cgc->buflen >> 8;
	cgc->cmd[9] = cgc->buflen & 0xff;

	ret = cdo->generic_packet(cdi, cgc);
	if (ret)
		return ret;

	s->copyright.cpst = buf[4];
	s->copyright.rmi = buf[5];

	return 0;
}