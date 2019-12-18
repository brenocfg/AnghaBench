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
struct tcpcb {int t_maxseg; } ;
struct bwmeas {int bw_minsizepkts; int bw_minsize; } ;

/* Variables and functions */
 int TCP_BWMEAS_BURST_MINSIZE ; 
 int /*<<< orphan*/  bwmeas_elm_size ; 
 int /*<<< orphan*/  bzero (struct bwmeas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_bwmeas_zone ; 
 struct bwmeas* zalloc (int /*<<< orphan*/ ) ; 

struct bwmeas *
tcp_bwmeas_alloc(struct tcpcb *tp)
{
	struct bwmeas *elm;
	elm = zalloc(tcp_bwmeas_zone);
	if (elm == NULL)
		return (elm);

	bzero(elm, bwmeas_elm_size);
	elm->bw_minsizepkts = TCP_BWMEAS_BURST_MINSIZE;
	elm->bw_minsize = elm->bw_minsizepkts * tp->t_maxseg;
	return (elm);
}