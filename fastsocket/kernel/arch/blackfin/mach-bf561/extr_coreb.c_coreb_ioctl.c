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
#define  CMD_COREB_RESET 130 
#define  CMD_COREB_START 129 
#define  CMD_COREB_STOP 128 
 int /*<<< orphan*/  CSYNC () ; 
 int EINVAL ; 
 int bfin_read_SICA_SYSCR () ; 
 int bfin_read_SICB_SYSCR () ; 
 int /*<<< orphan*/  bfin_write_SICA_SYSCR (int) ; 
 int /*<<< orphan*/  bfin_write_SICB_SYSCR (int) ; 

__attribute__((used)) static int
coreb_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret = 0;

	switch (cmd) {
	case CMD_COREB_START:
		bfin_write_SICA_SYSCR(bfin_read_SICA_SYSCR() & ~0x0020);
		break;
	case CMD_COREB_STOP:
		bfin_write_SICA_SYSCR(bfin_read_SICA_SYSCR() | 0x0020);
		bfin_write_SICB_SYSCR(bfin_read_SICB_SYSCR() | 0x0080);
		break;
	case CMD_COREB_RESET:
		bfin_write_SICB_SYSCR(bfin_read_SICB_SYSCR() | 0x0080);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	CSYNC();

	return ret;
}