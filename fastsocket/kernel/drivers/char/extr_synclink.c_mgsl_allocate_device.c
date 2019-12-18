#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int close_delay; int closing_wait; int /*<<< orphan*/ * ops; } ;
struct mgsl_struct {int max_frame_size; int num_tx_dma_buffers; scalar_t__ num_tx_holding_buffers; int /*<<< orphan*/  idle_mode; int /*<<< orphan*/  params; int /*<<< orphan*/  netlock; int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; TYPE_1__ port; int /*<<< orphan*/  task; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  MGSL_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDLC_TXIDLE_FLAGS ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGSL_MAGIC ; 
 int /*<<< orphan*/  default_params ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct mgsl_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mgsl_bh_handler ; 
 int /*<<< orphan*/  mgsl_port_ops ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_1__*) ; 

__attribute__((used)) static struct mgsl_struct* mgsl_allocate_device(void)
{
	struct mgsl_struct *info;
	
	info = kzalloc(sizeof(struct mgsl_struct),
		 GFP_KERNEL);
		 
	if (!info) {
		printk("Error can't allocate device instance data\n");
	} else {
		tty_port_init(&info->port);
		info->port.ops = &mgsl_port_ops;
		info->magic = MGSL_MAGIC;
		INIT_WORK(&info->task, mgsl_bh_handler);
		info->max_frame_size = 4096;
		info->port.close_delay = 5*HZ/10;
		info->port.closing_wait = 30*HZ;
		init_waitqueue_head(&info->status_event_wait_q);
		init_waitqueue_head(&info->event_wait_q);
		spin_lock_init(&info->irq_spinlock);
		spin_lock_init(&info->netlock);
		memcpy(&info->params,&default_params,sizeof(MGSL_PARAMS));
		info->idle_mode = HDLC_TXIDLE_FLAGS;		
		info->num_tx_dma_buffers = 1;
		info->num_tx_holding_buffers = 0;
	}
	
	return info;

}