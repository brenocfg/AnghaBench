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
struct tty_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENOIOCTLCMD ; 
#define  TCGETS 136 
#define  TCSETS 135 
#define  TIOCGICOUNT 134 
#define  TIOCGSERIAL 133 
#define  TIOCMIWAIT 132 
#define  TIOCSERCONFIG 131 
#define  TIOCSERGETLSR 130 
#define  TIOCSERGSTRUCT 129 
#define  TIOCSSERIAL 128 

__attribute__((used)) static int rfcomm_tty_ioctl(struct tty_struct *tty, struct file *filp, unsigned int cmd, unsigned long arg)
{
	BT_DBG("tty %p cmd 0x%02x", tty, cmd);

	switch (cmd) {
	case TCGETS:
		BT_DBG("TCGETS is not supported");
		return -ENOIOCTLCMD;

	case TCSETS:
		BT_DBG("TCSETS is not supported");
		return -ENOIOCTLCMD;

	case TIOCMIWAIT:
		BT_DBG("TIOCMIWAIT");
		break;

	case TIOCGICOUNT:
		BT_DBG("TIOCGICOUNT");
		break;

	case TIOCGSERIAL:
		BT_ERR("TIOCGSERIAL is not supported");
		return -ENOIOCTLCMD;

	case TIOCSSERIAL:
		BT_ERR("TIOCSSERIAL is not supported");
		return -ENOIOCTLCMD;

	case TIOCSERGSTRUCT:
		BT_ERR("TIOCSERGSTRUCT is not supported");
		return -ENOIOCTLCMD;

	case TIOCSERGETLSR:
		BT_ERR("TIOCSERGETLSR is not supported");
		return -ENOIOCTLCMD;

	case TIOCSERCONFIG:
		BT_ERR("TIOCSERCONFIG is not supported");
		return -ENOIOCTLCMD;

	default:
		return -ENOIOCTLCMD;	/* ioctls which we must ignore */

	}

	return -ENOIOCTLCMD;
}