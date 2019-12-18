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
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct inpcb {scalar_t__ inp_lport; int /*<<< orphan*/  in6p_laddr; TYPE_1__ inp_laddr; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 scalar_t__ INADDR_ANY ; 

__attribute__((used)) static boolean_t
flow_divert_has_pcb_local_address(const struct inpcb *inp)
{
	return (inp->inp_lport != 0
		&& (inp->inp_laddr.s_addr != INADDR_ANY || !IN6_IS_ADDR_UNSPECIFIED(&inp->in6p_laddr)));
}