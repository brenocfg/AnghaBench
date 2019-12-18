#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  jiffies; int /*<<< orphan*/  status; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct TYPE_7__ {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_STATUS ; 
 int OLOGSIZE ; 
 int /*<<< orphan*/  command_status ; 
 int /*<<< orphan*/  cont ; 
 int /*<<< orphan*/  current_req ; 
 scalar_t__ do_floppy ; 
 int /*<<< orphan*/  fd_inb (int /*<<< orphan*/ ) ; 
 TYPE_2__ fd_timeout ; 
 TYPE_2__ fd_timer ; 
 int /*<<< orphan*/  fdc_busy ; 
 TYPE_1__ floppy_work ; 
 scalar_t__ interruptjiffies ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lasthandler ; 
 int /*<<< orphan*/  lastredo ; 
 TYPE_3__* output_log ; 
 int output_log_pos ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/ * reply_buffer ; 
 int /*<<< orphan*/  resultjiffies ; 
 int resultsize ; 
 int /*<<< orphan*/  timeout_message ; 
 scalar_t__ timer_pending (TYPE_2__*) ; 
 scalar_t__ work_pending (TYPE_1__*) ; 

__attribute__((used)) static void show_floppy(void)
{
	int i;

	printk("\n");
	printk("floppy driver state\n");
	printk("-------------------\n");
	printk("now=%lu last interrupt=%lu diff=%lu last called handler=%p\n",
	       jiffies, interruptjiffies, jiffies - interruptjiffies,
	       lasthandler);

#ifdef FLOPPY_SANITY_CHECK
	printk("timeout_message=%s\n", timeout_message);
	printk("last output bytes:\n");
	for (i = 0; i < OLOGSIZE; i++)
		printk("%2x %2x %lu\n",
		       output_log[(i + output_log_pos) % OLOGSIZE].data,
		       output_log[(i + output_log_pos) % OLOGSIZE].status,
		       output_log[(i + output_log_pos) % OLOGSIZE].jiffies);
	printk("last result at %lu\n", resultjiffies);
	printk("last redo_fd_request at %lu\n", lastredo);
	for (i = 0; i < resultsize; i++) {
		printk("%2x ", reply_buffer[i]);
	}
	printk("\n");
#endif

	printk("status=%x\n", fd_inb(FD_STATUS));
	printk("fdc_busy=%lu\n", fdc_busy);
	if (do_floppy)
		printk("do_floppy=%p\n", do_floppy);
	if (work_pending(&floppy_work))
		printk("floppy_work.func=%p\n", floppy_work.func);
	if (timer_pending(&fd_timer))
		printk("fd_timer.function=%p\n", fd_timer.function);
	if (timer_pending(&fd_timeout)) {
		printk("timer_function=%p\n", fd_timeout.function);
		printk("expires=%lu\n", fd_timeout.expires - jiffies);
		printk("now=%lu\n", jiffies);
	}
	printk("cont=%p\n", cont);
	printk("current_req=%p\n", current_req);
	printk("command_status=%d\n", command_status);
	printk("\n");
}