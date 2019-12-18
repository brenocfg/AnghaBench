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
struct request_sense {int dummy; } ;
struct packet_command {unsigned int buflen; scalar_t__ data_direction; int stat; int /*<<< orphan*/  timeout; int /*<<< orphan*/  sense; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cmd; scalar_t__ quiet; } ;
struct cdrom_device_info {int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_WAIT_PC ; 
 scalar_t__ CGC_DATA_WRITE ; 
 unsigned int REQ_QUIET ; 
 unsigned int REQ_WRITE ; 
 int ide_cd_queue_pc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ide_cdrom_packet(struct cdrom_device_info *cdi,
			    struct packet_command *cgc)
{
	ide_drive_t *drive = cdi->handle;
	unsigned int flags = 0;
	unsigned len = cgc->buflen;

	if (cgc->timeout <= 0)
		cgc->timeout = ATAPI_WAIT_PC;

	/* here we queue the commands from the uniform CD-ROM
	   layer. the packet must be complete, as we do not
	   touch it at all. */

	if (cgc->data_direction == CGC_DATA_WRITE)
		flags |= REQ_WRITE;

	if (cgc->sense)
		memset(cgc->sense, 0, sizeof(struct request_sense));

	if (cgc->quiet)
		flags |= REQ_QUIET;

	cgc->stat = ide_cd_queue_pc(drive, cgc->cmd,
				    cgc->data_direction == CGC_DATA_WRITE,
				    cgc->buffer, &len,
				    cgc->sense, cgc->timeout, flags);
	if (!cgc->stat)
		cgc->buflen -= len;
	return cgc->stat;
}