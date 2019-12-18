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
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct bfa_port_s {int /*<<< orphan*/  (* stats_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  stats_cbarg; int /*<<< orphan*/  stats_reset_time; int /*<<< orphan*/  stats_busy; int /*<<< orphan*/  stats_status; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_port_clear_stats_isr(struct bfa_port_s *port, bfa_status_t status)
{
	struct timeval tv;

	port->stats_status = status;
	port->stats_busy   = BFA_FALSE;

	/*
	* re-initialize time stamp for stats reset
	*/
	do_gettimeofday(&tv);
	port->stats_reset_time = tv.tv_sec;

	if (port->stats_cbfn) {
		port->stats_cbfn(port->stats_cbarg, status);
		port->stats_cbfn = NULL;
	}
}