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
struct sep_device {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct sep_device* private_data; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  SEP_IOCADDFLOWMESSAGE 145 
#define  SEP_IOCADDFLOWTABLE 144 
#define  SEP_IOCALLOCDATAPOLL 143 
#define  SEP_IOCCREATEFLOWDMATABLE 142 
#define  SEP_IOCCREATESYMDMATABLE 141 
#define  SEP_IOCENDTRANSACTION 140 
#define  SEP_IOCFREEDMATABLEDATA 139 
#define  SEP_IOCGETIME 138 
#define  SEP_IOCGETMAPPEDADDROFFSET 137 
#define  SEP_IOCGETSTATICPOOLADDR 136 
#define  SEP_IOCREADDATAPOLL 135 
#define  SEP_IOCREALLOCCACHERES 134 
#define  SEP_IOCSENDSEPCOMMAND 133 
#define  SEP_IOCSENDSEPRPLYCOMMAND 132 
#define  SEP_IOCSEPINIT 131 
#define  SEP_IOCSEPSTART 130 
#define  SEP_IOCSETFLOWID 129 
#define  SEP_IOCWRITEDATAPOLL 128 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  edbg (char*,...) ; 
 int sep_add_flow_tables_handler (struct sep_device*,unsigned long) ; 
 int sep_add_flow_tables_message_handler (struct sep_device*,unsigned long) ; 
 int sep_allocate_data_pool_memory_handler (struct sep_device*,unsigned long) ; 
 int sep_create_flow_dma_tables_handler (struct sep_device*,unsigned long) ; 
 int sep_create_sync_dma_tables_handler (struct sep_device*,unsigned long) ; 
 int sep_end_transaction_handler (struct sep_device*,unsigned long) ; 
 int sep_free_dma_table_data_handler (struct sep_device*) ; 
 int sep_get_physical_mapped_offset_handler (struct sep_device*,unsigned long) ; 
 int sep_get_static_pool_addr_handler (struct sep_device*,unsigned long) ; 
 int sep_get_time_handler (struct sep_device*,unsigned long) ; 
 int sep_init_handler (struct sep_device*,unsigned long) ; 
 int sep_read_from_data_pool_handler (struct sep_device*,unsigned long) ; 
 int sep_realloc_cache_resident_handler (struct sep_device*,unsigned long) ; 
 int /*<<< orphan*/  sep_send_command_handler (struct sep_device*) ; 
 int /*<<< orphan*/  sep_send_reply_command_handler (struct sep_device*) ; 
 int sep_set_flow_id_handler (struct sep_device*,unsigned long) ; 
 int sep_start_handler (struct sep_device*) ; 
 int sep_write_into_data_pool_handler (struct sep_device*,unsigned long) ; 

__attribute__((used)) static int sep_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int error = 0;
	struct sep_device *sep = filp->private_data;

	dbg("------------>SEP Driver: ioctl start\n");

	edbg("SEP Driver: cmd is %x\n", cmd);

	switch (cmd) {
	case SEP_IOCSENDSEPCOMMAND:
		/* send command to SEP */
		sep_send_command_handler(sep);
		edbg("SEP Driver: after sep_send_command_handler\n");
		break;
	case SEP_IOCSENDSEPRPLYCOMMAND:
		/* send reply command to SEP */
		sep_send_reply_command_handler(sep);
		break;
	case SEP_IOCALLOCDATAPOLL:
		/* allocate data pool */
		error = sep_allocate_data_pool_memory_handler(sep, arg);
		break;
	case SEP_IOCWRITEDATAPOLL:
		/* write data into memory pool */
		error = sep_write_into_data_pool_handler(sep, arg);
		break;
	case SEP_IOCREADDATAPOLL:
		/* read data from data pool into application memory */
		error = sep_read_from_data_pool_handler(sep, arg);
		break;
	case SEP_IOCCREATESYMDMATABLE:
		/* create dma table for synhronic operation */
		error = sep_create_sync_dma_tables_handler(sep, arg);
		break;
	case SEP_IOCCREATEFLOWDMATABLE:
		/* create flow dma tables */
		error = sep_create_flow_dma_tables_handler(sep, arg);
		break;
	case SEP_IOCFREEDMATABLEDATA:
		/* free the pages */
		error = sep_free_dma_table_data_handler(sep);
		break;
	case SEP_IOCSETFLOWID:
		/* set flow id */
		error = sep_set_flow_id_handler(sep, (unsigned long)arg);
		break;
	case SEP_IOCADDFLOWTABLE:
		/* add tables to the dynamic flow */
		error = sep_add_flow_tables_handler(sep, arg);
		break;
	case SEP_IOCADDFLOWMESSAGE:
		/* add message of add tables to flow */
		error = sep_add_flow_tables_message_handler(sep, arg);
		break;
	case SEP_IOCSEPSTART:
		/* start command to sep */
		error = sep_start_handler(sep);
		break;
	case SEP_IOCSEPINIT:
		/* init command to sep */
		error = sep_init_handler(sep, arg);
		break;
	case SEP_IOCGETSTATICPOOLADDR:
		/* get the physical and virtual addresses of the static pool */
		error = sep_get_static_pool_addr_handler(sep, arg);
		break;
	case SEP_IOCENDTRANSACTION:
		error = sep_end_transaction_handler(sep, arg);
		break;
	case SEP_IOCREALLOCCACHERES:
		error = sep_realloc_cache_resident_handler(sep, arg);
		break;
	case SEP_IOCGETMAPPEDADDROFFSET:
		error = sep_get_physical_mapped_offset_handler(sep, arg);
		break;
	case SEP_IOCGETIME:
		error = sep_get_time_handler(sep, arg);
		break;
	default:
		error = -ENOTTY;
		break;
	}
	dbg("SEP Driver:<-------- ioctl end\n");
	return error;
}