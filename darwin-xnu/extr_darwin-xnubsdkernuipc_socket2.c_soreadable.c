#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tqh_first; } ;
struct TYPE_3__ {scalar_t__ sb_cc; scalar_t__ sb_lowat; } ;
struct socket {int so_state; scalar_t__ so_error; TYPE_2__ so_comp; TYPE_1__ so_rcv; } ;

/* Variables and functions */
 int SS_CANTRCVMORE ; 

int
soreadable(struct socket *so)
{
	return (so->so_rcv.sb_cc >= so->so_rcv.sb_lowat ||
	    ((so->so_state & SS_CANTRCVMORE)
#if CONTENT_FILTER
	    && cfil_sock_data_pending(&so->so_rcv) == 0
#endif /* CONTENT_FILTER */
	    ) ||
	    so->so_comp.tqh_first || so->so_error);
}