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
struct sge {int /*<<< orphan*/  adapter; struct sched* tx_sched; } ;
struct sched_port {unsigned int speed; unsigned int mtu; unsigned int drain_bits_per_1024ns; } ;
struct sched {int max_avail; struct sched_port* p; } ;
struct TYPE_2__ {scalar_t__ board; } ;

/* Variables and functions */
 scalar_t__ CHBT_BOARD_CHT204 ; 
 TYPE_1__* board_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 void* max (unsigned int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 

unsigned int t1_sched_update_parms(struct sge *sge, unsigned int port,
				   unsigned int mtu, unsigned int speed)
{
	struct sched *s = sge->tx_sched;
	struct sched_port *p = &s->p[port];
	unsigned int max_avail_segs;

	pr_debug("t1_sched_update_params mtu=%d speed=%d\n", mtu, speed);
	if (speed)
		p->speed = speed;
	if (mtu)
		p->mtu = mtu;

	if (speed || mtu) {
		unsigned long long drain = 1024ULL * p->speed * (p->mtu - 40);
		do_div(drain, (p->mtu + 50) * 1000);
		p->drain_bits_per_1024ns = (unsigned int) drain;

		if (p->speed < 1000)
			p->drain_bits_per_1024ns =
				90 * p->drain_bits_per_1024ns / 100;
	}

	if (board_info(sge->adapter)->board == CHBT_BOARD_CHT204) {
		p->drain_bits_per_1024ns -= 16;
		s->max_avail = max(4096U, p->mtu + 16 + 14 + 4);
		max_avail_segs = max(1U, 4096 / (p->mtu - 40));
	} else {
		s->max_avail = 16384;
		max_avail_segs = max(1U, 9000 / (p->mtu - 40));
	}

	pr_debug("t1_sched_update_parms: mtu %u speed %u max_avail %u "
		 "max_avail_segs %u drain_bits_per_1024ns %u\n", p->mtu,
		 p->speed, s->max_avail, max_avail_segs,
		 p->drain_bits_per_1024ns);

	return max_avail_segs * (p->mtu - 40);
}