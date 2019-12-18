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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct sgentryraw {int dummy; } ;
struct sge_ieee1212 {int dummy; } ;
struct scsi_cmnd {int dummy; } ;
struct fib {struct aac_dev* dev; } ;
struct aac_raw_io2 {int /*<<< orphan*/  sgeCnt; void* flags; void* cid; void* byteCount; void* blockHigh; void* blockLow; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct aac_raw_io {TYPE_2__ sg; scalar_t__ bpComplete; scalar_t__ bpTotal; void* flags; void* cid; void* count; void** block; } ;
struct aac_fibhdr {int dummy; } ;
struct aac_dev {scalar_t__ comm_interface; int max_fib_size; int /*<<< orphan*/  cache_protected; TYPE_1__* scsi_host_ptr; int /*<<< orphan*/  sync_mode; } ;
typedef  int /*<<< orphan*/  fib_callback ;
struct TYPE_3__ {int /*<<< orphan*/  sg_tablesize; } ;

/* Variables and functions */
 scalar_t__ AAC_COMM_MESSAGE_TYPE2 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ContainerRawIo ; 
 int ContainerRawIo2 ; 
 int /*<<< orphan*/  FsaNormal ; 
 int RIO2_IO_SUREWRITE ; 
 int RIO2_IO_TYPE_WRITE ; 
 int RIO_SUREWRITE ; 
 int RIO_TYPE_WRITE ; 
 int /*<<< orphan*/  aac_build_sgraw (struct scsi_cmnd*,TYPE_2__*) ; 
 int /*<<< orphan*/  aac_build_sgraw2 (struct scsi_cmnd*,struct aac_raw_io2*,int /*<<< orphan*/ ) ; 
 int aac_cache ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int,struct fib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ fib_data (struct fib*) ; 
 scalar_t__ io_callback ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aac_raw_io2*,int /*<<< orphan*/ ,int) ; 
 int scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_write_raw_io(struct fib * fib, struct scsi_cmnd * cmd, u64 lba, u32 count, int fua)
{
	struct aac_dev *dev = fib->dev;
	u16 fibsize, command;

	aac_fib_init(fib);
	if (dev->comm_interface == AAC_COMM_MESSAGE_TYPE2 && !dev->sync_mode) {
		struct aac_raw_io2 *writecmd2;
		writecmd2 = (struct aac_raw_io2 *) fib_data(fib);
		memset(writecmd2, 0, sizeof(struct aac_raw_io2));
		writecmd2->blockLow = cpu_to_le32((u32)(lba&0xffffffff));
		writecmd2->blockHigh = cpu_to_le32((u32)((lba&0xffffffff00000000LL)>>32));
		writecmd2->byteCount = cpu_to_le32(count<<9);
		writecmd2->cid = cpu_to_le16(scmd_id(cmd));
		writecmd2->flags = (fua && ((aac_cache & 5) != 1) &&
						   (((aac_cache & 5) != 5) || !fib->dev->cache_protected)) ?
			cpu_to_le16(RIO2_IO_TYPE_WRITE|RIO2_IO_SUREWRITE) :
			cpu_to_le16(RIO2_IO_TYPE_WRITE);
		aac_build_sgraw2(cmd, writecmd2, dev->scsi_host_ptr->sg_tablesize);
		command = ContainerRawIo2;
		fibsize = sizeof(struct aac_raw_io2) +
			((le32_to_cpu(writecmd2->sgeCnt)-1) * sizeof(struct sge_ieee1212));
	} else {
		struct aac_raw_io *writecmd;
		writecmd = (struct aac_raw_io *) fib_data(fib);
		writecmd->block[0] = cpu_to_le32((u32)(lba&0xffffffff));
		writecmd->block[1] = cpu_to_le32((u32)((lba&0xffffffff00000000LL)>>32));
		writecmd->count = cpu_to_le32(count<<9);
		writecmd->cid = cpu_to_le16(scmd_id(cmd));
		writecmd->flags = (fua && ((aac_cache & 5) != 1) &&
						   (((aac_cache & 5) != 5) || !fib->dev->cache_protected)) ?
			cpu_to_le16(RIO_TYPE_WRITE|RIO_SUREWRITE) :
			cpu_to_le16(RIO_TYPE_WRITE);
		writecmd->bpTotal = 0;
		writecmd->bpComplete = 0;
		aac_build_sgraw(cmd, &writecmd->sg);
		command = ContainerRawIo;
		fibsize = sizeof(struct aac_raw_io) +
			((le32_to_cpu(writecmd->sg.count)-1) * sizeof (struct sgentryraw));
	}

	BUG_ON(fibsize > (fib->dev->max_fib_size - sizeof(struct aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	return aac_fib_send(command,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (void *) cmd);
}