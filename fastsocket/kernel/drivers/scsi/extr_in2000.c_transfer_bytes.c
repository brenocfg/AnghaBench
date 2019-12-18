#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct IN2000_hostdata {int* sync_xfer; scalar_t__ level2; unsigned short io_base; int /*<<< orphan*/  fifo; void* state; } ;
struct TYPE_11__ {int length; } ;
struct TYPE_9__ {int this_residual; scalar_t__ phase; int have_data_in; scalar_t__ ptr; TYPE_6__* buffer; scalar_t__ buffers_residual; } ;
struct TYPE_10__ {TYPE_3__ SCp; TYPE_2__* device; } ;
struct TYPE_8__ {size_t id; TYPE_1__* host; } ;
struct TYPE_7__ {scalar_t__ hostdata; } ;
typedef  TYPE_4__ Scsi_Cmnd ;

/* Variables and functions */
 int CTRL_BUS ; 
 int CTRL_EDI ; 
 int CTRL_IDI ; 
 int /*<<< orphan*/  FAST_WRITE2_IO () ; 
 int /*<<< orphan*/  FI_FIFO_READING ; 
 int /*<<< orphan*/  FI_FIFO_WRITING ; 
 int IN2000_FIFO_SIZE ; 
 unsigned short IO_FIFO ; 
 int /*<<< orphan*/  IO_FIFO_READ ; 
 int /*<<< orphan*/  IO_FIFO_WRITE ; 
 scalar_t__ L2_BASIC ; 
 scalar_t__ L2_DATA ; 
 void* S_RUNNING_LEVEL2 ; 
 int /*<<< orphan*/  WD_CMD_SEL_ATN_XFER ; 
 int /*<<< orphan*/  WD_CMD_TRANS_INFO ; 
 int /*<<< orphan*/  WD_COMMAND_PHASE ; 
 int /*<<< orphan*/  WD_CONTROL ; 
 int /*<<< orphan*/  WD_SYNCHRONOUS_TRANSFER ; 
 scalar_t__ sg_virt (TYPE_6__*) ; 
 int /*<<< orphan*/  write1_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write2_io (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  write_3393 (struct IN2000_hostdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_3393_cmd (struct IN2000_hostdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_3393_count (struct IN2000_hostdata*,int) ; 

__attribute__((used)) static void transfer_bytes(Scsi_Cmnd * cmd, int data_in_dir)
{
	struct IN2000_hostdata *hostdata;
	unsigned short *sp;
	unsigned short f;
	int i;

	hostdata = (struct IN2000_hostdata *) cmd->device->host->hostdata;

/* Normally, you'd expect 'this_residual' to be non-zero here.
 * In a series of scatter-gather transfers, however, this
 * routine will usually be called with 'this_residual' equal
 * to 0 and 'buffers_residual' non-zero. This means that a
 * previous transfer completed, clearing 'this_residual', and
 * now we need to setup the next scatter-gather buffer as the
 * source or destination for THIS transfer.
 */
	if (!cmd->SCp.this_residual && cmd->SCp.buffers_residual) {
		++cmd->SCp.buffer;
		--cmd->SCp.buffers_residual;
		cmd->SCp.this_residual = cmd->SCp.buffer->length;
		cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
	}

/* Set up hardware registers */

	write_3393(hostdata, WD_SYNCHRONOUS_TRANSFER, hostdata->sync_xfer[cmd->device->id]);
	write_3393_count(hostdata, cmd->SCp.this_residual);
	write_3393(hostdata, WD_CONTROL, CTRL_IDI | CTRL_EDI | CTRL_BUS);
	write1_io(0, IO_FIFO_WRITE);	/* zero counter, assume write */

/* Reading is easy. Just issue the command and return - we'll
 * get an interrupt later when we have actual data to worry about.
 */

	if (data_in_dir) {
		write1_io(0, IO_FIFO_READ);
		if ((hostdata->level2 >= L2_DATA) || (hostdata->level2 == L2_BASIC && cmd->SCp.phase == 0)) {
			write_3393(hostdata, WD_COMMAND_PHASE, 0x45);
			write_3393_cmd(hostdata, WD_CMD_SEL_ATN_XFER);
			hostdata->state = S_RUNNING_LEVEL2;
		} else
			write_3393_cmd(hostdata, WD_CMD_TRANS_INFO);
		hostdata->fifo = FI_FIFO_READING;
		cmd->SCp.have_data_in = 0;
		return;
	}

/* Writing is more involved - we'll start the WD chip and write as
 * much data to the fifo as we can right now. Later interrupts will
 * write any bytes that don't make it at this stage.
 */

	if ((hostdata->level2 >= L2_DATA) || (hostdata->level2 == L2_BASIC && cmd->SCp.phase == 0)) {
		write_3393(hostdata, WD_COMMAND_PHASE, 0x45);
		write_3393_cmd(hostdata, WD_CMD_SEL_ATN_XFER);
		hostdata->state = S_RUNNING_LEVEL2;
	} else
		write_3393_cmd(hostdata, WD_CMD_TRANS_INFO);
	hostdata->fifo = FI_FIFO_WRITING;
	sp = (unsigned short *) cmd->SCp.ptr;

	if ((i = cmd->SCp.this_residual) > IN2000_FIFO_SIZE)
		i = IN2000_FIFO_SIZE;
	cmd->SCp.have_data_in = i;
	i >>= 1;		/* Gulp. We assume this_residual is modulo 2 */
	f = hostdata->io_base + IO_FIFO;

#ifdef FAST_WRITE_IO

	FAST_WRITE2_IO();
#else
	while (i--)
		write2_io(*sp++, IO_FIFO);

#endif

}