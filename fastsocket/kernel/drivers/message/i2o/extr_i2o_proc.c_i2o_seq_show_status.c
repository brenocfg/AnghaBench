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
struct seq_file {scalar_t__ private; } ;
struct TYPE_3__ {TYPE_2__* virt; } ;
struct i2o_controller {TYPE_1__ status_block; } ;
struct TYPE_4__ {int org_id; int i2o_version; int iop_id; int host_unit_id; int segment_number; int iop_state; int msg_type; int inbound_frame_size; int max_inbound_frames; int cur_inbound_frames; int max_outbound_frames; int expected_lct_size; int iop_capabilities; int desired_mem_size; int current_mem_size; int current_mem_base; int desired_io_size; int current_io_size; int current_io_base; int /*<<< orphan*/  product_id; } ;
typedef  TYPE_2__ i2o_status_block ;

/* Variables and functions */
 int /*<<< orphan*/  i2o_status_get (struct i2o_controller*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int i2o_seq_show_status(struct seq_file *seq, void *v)
{
	struct i2o_controller *c = (struct i2o_controller *)seq->private;
	char prodstr[25];
	int version;
	i2o_status_block *sb = c->status_block.virt;

	i2o_status_get(c);	// reread the status block

	seq_printf(seq, "Organization ID        : %0#6x\n", sb->org_id);

	version = sb->i2o_version;

/* FIXME for Spec 2.0
	if (version == 0x02) {
		seq_printf(seq, "Lowest I2O version supported: ");
		switch(workspace[2]) {
			case 0x00:
				seq_printf(seq, "1.0\n");
				break;
			case 0x01:
				seq_printf(seq, "1.5\n");
				break;
			case 0x02:
				seq_printf(seq, "2.0\n");
				break;
		}

		seq_printf(seq, "Highest I2O version supported: ");
		switch(workspace[3]) {
			case 0x00:
				seq_printf(seq, "1.0\n");
				break;
			case 0x01:
				seq_printf(seq, "1.5\n");
				break;
			case 0x02:
				seq_printf(seq, "2.0\n");
				break;
		}
	}
*/
	seq_printf(seq, "IOP ID                 : %0#5x\n", sb->iop_id);
	seq_printf(seq, "Host Unit ID           : %0#6x\n", sb->host_unit_id);
	seq_printf(seq, "Segment Number         : %0#5x\n", sb->segment_number);

	seq_printf(seq, "I2O version            : ");
	switch (version) {
	case 0x00:
		seq_printf(seq, "1.0\n");
		break;
	case 0x01:
		seq_printf(seq, "1.5\n");
		break;
	case 0x02:
		seq_printf(seq, "2.0\n");
		break;
	default:
		seq_printf(seq, "Unknown version\n");
	}

	seq_printf(seq, "IOP State              : ");
	switch (sb->iop_state) {
	case 0x01:
		seq_printf(seq, "INIT\n");
		break;

	case 0x02:
		seq_printf(seq, "RESET\n");
		break;

	case 0x04:
		seq_printf(seq, "HOLD\n");
		break;

	case 0x05:
		seq_printf(seq, "READY\n");
		break;

	case 0x08:
		seq_printf(seq, "OPERATIONAL\n");
		break;

	case 0x10:
		seq_printf(seq, "FAILED\n");
		break;

	case 0x11:
		seq_printf(seq, "FAULTED\n");
		break;

	default:
		seq_printf(seq, "Unknown\n");
		break;
	}

	seq_printf(seq, "Messenger Type         : ");
	switch (sb->msg_type) {
	case 0x00:
		seq_printf(seq, "Memory mapped\n");
		break;
	case 0x01:
		seq_printf(seq, "Memory mapped only\n");
		break;
	case 0x02:
		seq_printf(seq, "Remote only\n");
		break;
	case 0x03:
		seq_printf(seq, "Memory mapped and remote\n");
		break;
	default:
		seq_printf(seq, "Unknown\n");
	}

	seq_printf(seq, "Inbound Frame Size     : %d bytes\n",
		   sb->inbound_frame_size << 2);
	seq_printf(seq, "Max Inbound Frames     : %d\n",
		   sb->max_inbound_frames);
	seq_printf(seq, "Current Inbound Frames : %d\n",
		   sb->cur_inbound_frames);
	seq_printf(seq, "Max Outbound Frames    : %d\n",
		   sb->max_outbound_frames);

	/* Spec doesn't say if NULL terminated or not... */
	memcpy(prodstr, sb->product_id, 24);
	prodstr[24] = '\0';
	seq_printf(seq, "Product ID             : %s\n", prodstr);
	seq_printf(seq, "Expected LCT Size      : %d bytes\n",
		   sb->expected_lct_size);

	seq_printf(seq, "IOP Capabilities\n");
	seq_printf(seq, "    Context Field Size Support : ");
	switch (sb->iop_capabilities & 0x0000003) {
	case 0:
		seq_printf(seq, "Supports only 32-bit context fields\n");
		break;
	case 1:
		seq_printf(seq, "Supports only 64-bit context fields\n");
		break;
	case 2:
		seq_printf(seq, "Supports 32-bit and 64-bit context fields, "
			   "but not concurrently\n");
		break;
	case 3:
		seq_printf(seq, "Supports 32-bit and 64-bit context fields "
			   "concurrently\n");
		break;
	default:
		seq_printf(seq, "0x%08x\n", sb->iop_capabilities);
	}
	seq_printf(seq, "    Current Context Field Size : ");
	switch (sb->iop_capabilities & 0x0000000C) {
	case 0:
		seq_printf(seq, "not configured\n");
		break;
	case 4:
		seq_printf(seq, "Supports only 32-bit context fields\n");
		break;
	case 8:
		seq_printf(seq, "Supports only 64-bit context fields\n");
		break;
	case 12:
		seq_printf(seq, "Supports both 32-bit or 64-bit context fields "
			   "concurrently\n");
		break;
	default:
		seq_printf(seq, "\n");
	}
	seq_printf(seq, "    Inbound Peer Support       : %s\n",
		   (sb->
		    iop_capabilities & 0x00000010) ? "Supported" :
		   "Not supported");
	seq_printf(seq, "    Outbound Peer Support      : %s\n",
		   (sb->
		    iop_capabilities & 0x00000020) ? "Supported" :
		   "Not supported");
	seq_printf(seq, "    Peer to Peer Support       : %s\n",
		   (sb->
		    iop_capabilities & 0x00000040) ? "Supported" :
		   "Not supported");

	seq_printf(seq, "Desired private memory size   : %d kB\n",
		   sb->desired_mem_size >> 10);
	seq_printf(seq, "Allocated private memory size : %d kB\n",
		   sb->current_mem_size >> 10);
	seq_printf(seq, "Private memory base address   : %0#10x\n",
		   sb->current_mem_base);
	seq_printf(seq, "Desired private I/O size      : %d kB\n",
		   sb->desired_io_size >> 10);
	seq_printf(seq, "Allocated private I/O size    : %d kB\n",
		   sb->current_io_size >> 10);
	seq_printf(seq, "Private I/O base address      : %0#10x\n",
		   sb->current_io_base);

	return 0;
}