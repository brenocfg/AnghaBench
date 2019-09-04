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
struct socket {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  socantsendmore (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
udp_shutdown(struct socket *so)
{
	struct inpcb *inp;

	inp = sotoinpcb(so);
	if (inp == NULL)
		return (EINVAL);
	socantsendmore(so);
	return (0);
}