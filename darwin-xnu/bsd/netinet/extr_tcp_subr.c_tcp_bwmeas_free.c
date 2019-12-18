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
struct tcpcb {int /*<<< orphan*/  t_flagsext; int /*<<< orphan*/ * t_bwmeas; } ;

/* Variables and functions */
 int /*<<< orphan*/  TF_MEASURESNDBW ; 
 int /*<<< orphan*/  tcp_bwmeas_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
tcp_bwmeas_free(struct tcpcb *tp)
{
	zfree(tcp_bwmeas_zone, tp->t_bwmeas);
	tp->t_bwmeas = NULL;
	tp->t_flagsext &= ~(TF_MEASURESNDBW);
}