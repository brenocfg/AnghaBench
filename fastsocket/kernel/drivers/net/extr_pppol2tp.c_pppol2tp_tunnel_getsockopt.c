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
struct sock {int dummy; } ;
struct pppol2tp_tunnel {int debug; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_CONTROL ; 
#define  PPPOL2TP_SO_DEBUG 128 
 int /*<<< orphan*/  PRINTK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pppol2tp_tunnel_getsockopt(struct sock *sk,
				      struct pppol2tp_tunnel *tunnel,
				      int optname, int *val)
{
	int err = 0;

	switch (optname) {
	case PPPOL2TP_SO_DEBUG:
		*val = tunnel->debug;
		PRINTK(tunnel->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
		       "%s: get debug=%x\n", tunnel->name, tunnel->debug);
		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	return err;
}