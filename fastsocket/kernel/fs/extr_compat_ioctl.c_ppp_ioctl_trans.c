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

/* Variables and functions */
 int EINVAL ; 
#define  PPPIOCGIDLE32 129 
#define  PPPIOCSCOMPRESS32 128 
 int ppp_gidle (unsigned int,unsigned int,unsigned long) ; 
 int ppp_scompress (unsigned int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int ppp_ioctl_trans(unsigned int fd, unsigned int cmd, unsigned long arg)
{
	int err;

	switch (cmd) {
	case PPPIOCGIDLE32:
		err = ppp_gidle(fd, cmd, arg);
		break;

	case PPPIOCSCOMPRESS32:
		err = ppp_scompress(fd, cmd, arg);
		break;

	default:
		do {
			static int count;
			if (++count <= 20)
				printk("ppp_ioctl: Unknown cmd fd(%d) "
				       "cmd(%08x) arg(%08x)\n",
				       (int)fd, (unsigned int)cmd, (unsigned int)arg);
		} while(0);
		err = -EINVAL;
		break;
	};

	return err;
}