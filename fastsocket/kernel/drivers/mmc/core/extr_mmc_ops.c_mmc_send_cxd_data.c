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
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct mmc_request {int flags; unsigned int blksz; int blocks; int sg_len; int timeout_clks; int error; scalar_t__ timeout_ns; struct scatterlist* sg; scalar_t__ arg; scalar_t__ opcode; struct mmc_request* data; struct mmc_request* cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int flags; unsigned int blksz; int blocks; int sg_len; int timeout_clks; int error; scalar_t__ timeout_ns; struct scatterlist* sg; scalar_t__ arg; scalar_t__ opcode; struct mmc_data* data; struct mmc_data* cmd; } ;
struct mmc_command {int flags; unsigned int blksz; int blocks; int sg_len; int timeout_clks; int error; scalar_t__ timeout_ns; struct scatterlist* sg; scalar_t__ arg; scalar_t__ opcode; struct mmc_command* data; struct mmc_command* cmd; } ;
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MMC_CMD_ADTC ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_SPI_R1 ; 
 scalar_t__ MMC_SEND_CID ; 
 scalar_t__ MMC_SEND_CSD ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct mmc_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_set_data_timeout (struct mmc_request*,struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_wait_for_req (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,unsigned int) ; 

__attribute__((used)) static int
mmc_send_cxd_data(struct mmc_card *card, struct mmc_host *host,
		u32 opcode, void *buf, unsigned len)
{
	struct mmc_request mrq;
	struct mmc_command cmd;
	struct mmc_data data;
	struct scatterlist sg;
	void *data_buf;

	/* dma onto stack is unsafe/nonportable, but callers to this
	 * routine normally provide temporary on-stack buffers ...
	 */
	data_buf = kmalloc(len, GFP_KERNEL);
	if (data_buf == NULL)
		return -ENOMEM;

	memset(&mrq, 0, sizeof(struct mmc_request));
	memset(&cmd, 0, sizeof(struct mmc_command));
	memset(&data, 0, sizeof(struct mmc_data));

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = opcode;
	cmd.arg = 0;

	/* NOTE HACK:  the MMC_RSP_SPI_R1 is always correct here, but we
	 * rely on callers to never use this with "native" calls for reading
	 * CSD or CID.  Native versions of those commands use the R2 type,
	 * not R1 plus a data block.
	 */
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = len;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, data_buf, len);

	if (opcode == MMC_SEND_CSD || opcode == MMC_SEND_CID) {
		/*
		 * The spec states that CSR and CID accesses have a timeout
		 * of 64 clock cycles.
		 */
		data.timeout_ns = 0;
		data.timeout_clks = 64;
	} else
		mmc_set_data_timeout(&data, card);

	mmc_wait_for_req(host, &mrq);

	memcpy(buf, data_buf, len);
	kfree(data_buf);

	if (cmd.error)
		return cmd.error;
	if (data.error)
		return data.error;

	return 0;
}