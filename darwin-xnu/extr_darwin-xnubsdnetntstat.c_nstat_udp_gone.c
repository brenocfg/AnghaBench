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
struct nstat_tucookie {struct inpcb* inp; } ;
struct inpcb {scalar_t__ inp_state; } ;
typedef  scalar_t__ nstat_provider_cookie_t ;

/* Variables and functions */
 scalar_t__ INPCB_STATE_DEAD ; 

__attribute__((used)) static int
nstat_udp_gone(
	nstat_provider_cookie_t	cookie)
{
	struct nstat_tucookie *tucookie =
	    (struct nstat_tucookie *)cookie;
	struct inpcb *inp;

	return (!(inp = tucookie->inp) ||
		inp->inp_state == INPCB_STATE_DEAD) ? 1 : 0;
}