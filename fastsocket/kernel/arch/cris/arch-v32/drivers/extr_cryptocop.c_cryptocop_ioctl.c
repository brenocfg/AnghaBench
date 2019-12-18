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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
#define  CRYPTOCOP_IO_CLOSE_SESSION 130 
#define  CRYPTOCOP_IO_CREATE_SESSION 129 
 scalar_t__ CRYPTOCOP_IO_MAXNR ; 
#define  CRYPTOCOP_IO_PROCESS_OP 128 
 int /*<<< orphan*/  DEBUG_API (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int ENOTTY ; 
 scalar_t__ ETRAXCRYPTOCOP_IOCTYPE ; 
 int /*<<< orphan*/  VERIFY_READ ; 
 int /*<<< orphan*/  VERIFY_WRITE ; 
 int _IOC_DIR (unsigned int) ; 
 scalar_t__ _IOC_NR (unsigned int) ; 
 int _IOC_READ ; 
 int /*<<< orphan*/  _IOC_SIZE (unsigned int) ; 
 scalar_t__ _IOC_TYPE (unsigned int) ; 
 int _IOC_WRITE ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int cryptocop_ioctl_close_session (struct inode*,struct file*,unsigned int,unsigned long) ; 
 int cryptocop_ioctl_create_session (struct inode*,struct file*,unsigned int,unsigned long) ; 
 int cryptocop_ioctl_process (struct inode*,struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int cryptocop_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int err = 0;
	if (_IOC_TYPE(cmd) != ETRAXCRYPTOCOP_IOCTYPE) {
		DEBUG_API(printk("cryptocop_ioctl: wrong type\n"));
		return -ENOTTY;
	}
	if (_IOC_NR(cmd) > CRYPTOCOP_IO_MAXNR){
		return -ENOTTY;
	}
	/* Access check of the argument.  Some commands, e.g. create session and process op,
	   needs additional checks.  Those are handled in the command handling functions. */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch (cmd) {
	case CRYPTOCOP_IO_CREATE_SESSION:
		return cryptocop_ioctl_create_session(inode, filp, cmd, arg);
	case CRYPTOCOP_IO_CLOSE_SESSION:
		return cryptocop_ioctl_close_session(inode, filp, cmd, arg);
	case CRYPTOCOP_IO_PROCESS_OP:
		return cryptocop_ioctl_process(inode, filp, cmd, arg);
	default:
		DEBUG_API(printk("cryptocop_ioctl: unknown command\n"));
		return -ENOTTY;
	}
	return 0;
}