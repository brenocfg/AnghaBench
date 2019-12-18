#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rwrt_feature_desc {int curr; void* feature_code; } ;
struct packet_command {unsigned int buflen; int* cmd; int stat; TYPE_2__* sense; scalar_t__ buffer; } ;
struct feature_header {int dummy; } ;
struct cdrom_device_info {int mask; TYPE_1__* ops; } ;
struct TYPE_6__ {int erasable; void* disc_information_length; } ;
typedef  TYPE_3__ disc_information ;
struct TYPE_5__ {int sense_key; int asc; int ascq; } ;
struct TYPE_4__ {int capability; } ;

/* Variables and functions */
 int CDC_DVD_RAM ; 
 int CDC_RAM ; 
 int CDF_RWRT ; 
 int EIO ; 
#define  GPCMD_GET_CONFIGURATION 129 
#define  GPCMD_READ_DISC_INFO 128 
 void* cpu_to_be16 (int) ; 

__attribute__((used)) static int viocd_packet(struct cdrom_device_info *cdi,
		struct packet_command *cgc)
{
	unsigned int buflen = cgc->buflen;
	int ret = -EIO;

	switch (cgc->cmd[0]) {
	case GPCMD_READ_DISC_INFO:
		{
			disc_information *di = (disc_information *)cgc->buffer;

			if (buflen >= 2) {
				di->disc_information_length = cpu_to_be16(1);
				ret = 0;
			}
			if (buflen >= 3)
				di->erasable =
					(cdi->ops->capability & ~cdi->mask
					 & (CDC_DVD_RAM | CDC_RAM)) != 0;
		}
		break;
	case GPCMD_GET_CONFIGURATION:
		if (cgc->cmd[3] == CDF_RWRT) {
			struct rwrt_feature_desc *rfd = (struct rwrt_feature_desc *)(cgc->buffer + sizeof(struct feature_header));

			if ((buflen >=
			     (sizeof(struct feature_header) + sizeof(*rfd))) &&
			    (cdi->ops->capability & ~cdi->mask
			     & (CDC_DVD_RAM | CDC_RAM))) {
				rfd->feature_code = cpu_to_be16(CDF_RWRT);
				rfd->curr = 1;
				ret = 0;
			}
		}
		break;
	default:
		if (cgc->sense) {
			/* indicate Unknown code */
			cgc->sense->sense_key = 0x05;
			cgc->sense->asc = 0x20;
			cgc->sense->ascq = 0x00;
		}
		break;
	}

	cgc->stat = ret;
	return ret;
}