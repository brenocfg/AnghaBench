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
struct scsi_cd {int dummy; } ;
struct packet_command {int* cmd; unsigned char* buffer; int buflen; int quiet; int /*<<< orphan*/  data_direction; int /*<<< orphan*/  timeout; } ;
struct cdrom_tochdr {unsigned char cdth_trk0; unsigned char cdth_trk1; } ;
struct cdrom_device_info {struct scsi_cd* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int GPCMD_READ_TOC_PMA_ATIP ; 
 int /*<<< orphan*/  IOCTL_TIMEOUT ; 
 int SR_GFP_DMA (struct scsi_cd*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int) ; 
 int /*<<< orphan*/  memset (struct packet_command*,int /*<<< orphan*/ ,int) ; 
 int sr_do_ioctl (struct scsi_cd*,struct packet_command*) ; 

__attribute__((used)) static int sr_read_tochdr(struct cdrom_device_info *cdi,
		struct cdrom_tochdr *tochdr)
{
	struct scsi_cd *cd = cdi->handle;
	struct packet_command cgc;
	int result;
	unsigned char *buffer;

	buffer = kmalloc(32, GFP_KERNEL | SR_GFP_DMA(cd));
	if (!buffer)
		return -ENOMEM;

	memset(&cgc, 0, sizeof(struct packet_command));
	cgc.timeout = IOCTL_TIMEOUT;
	cgc.cmd[0] = GPCMD_READ_TOC_PMA_ATIP;
	cgc.cmd[8] = 12;		/* LSB of length */
	cgc.buffer = buffer;
	cgc.buflen = 12;
	cgc.quiet = 1;
	cgc.data_direction = DMA_FROM_DEVICE;

	result = sr_do_ioctl(cd, &cgc);

	tochdr->cdth_trk0 = buffer[2];
	tochdr->cdth_trk1 = buffer[3];

	kfree(buffer);
	return result;
}