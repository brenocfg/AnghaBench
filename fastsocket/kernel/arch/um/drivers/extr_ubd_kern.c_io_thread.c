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
struct io_thread_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_io (struct io_thread_req*) ; 
 int /*<<< orphan*/  ignore_sigwinch_sig () ; 
 int /*<<< orphan*/  io_count ; 
 int /*<<< orphan*/  kernel_fd ; 
 int os_read_file (int /*<<< orphan*/ ,struct io_thread_req**,int) ; 
 int os_write_file (int /*<<< orphan*/ ,struct io_thread_req**,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 

int io_thread(void *arg)
{
	struct io_thread_req *req;
	int n;

	ignore_sigwinch_sig();
	while(1){
		n = os_read_file(kernel_fd, &req,
				 sizeof(struct io_thread_req *));
		if(n != sizeof(struct io_thread_req *)){
			if(n < 0)
				printk("io_thread - read failed, fd = %d, "
				       "err = %d\n", kernel_fd, -n);
			else {
				printk("io_thread - short read, fd = %d, "
				       "length = %d\n", kernel_fd, n);
			}
			continue;
		}
		io_count++;
		do_io(req);
		n = os_write_file(kernel_fd, &req,
				  sizeof(struct io_thread_req *));
		if(n != sizeof(struct io_thread_req *))
			printk("io_thread - write failed, fd = %d, err = %d\n",
			       kernel_fd, -n);
	}

	return 0;
}