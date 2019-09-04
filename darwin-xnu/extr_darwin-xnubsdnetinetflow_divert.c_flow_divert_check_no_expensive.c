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
struct inpcb {scalar_t__ inp_last_outifp; } ;
struct flow_divert_pcb {int /*<<< orphan*/  so; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHOSTUNREACH ; 
 scalar_t__ IFNET_IS_EXPENSIVE (scalar_t__) ; 
 scalar_t__ INP_NO_EXPENSIVE (struct inpcb*) ; 
 struct inpcb* sotoinpcb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
flow_divert_check_no_expensive(struct flow_divert_pcb *fd_cb)
{
	struct inpcb *inp = NULL;

	inp = sotoinpcb(fd_cb->so);
	if (inp && INP_NO_EXPENSIVE(inp) && inp->inp_last_outifp &&
	    IFNET_IS_EXPENSIVE(inp->inp_last_outifp))
		return EHOSTUNREACH;
	
	return 0;
}