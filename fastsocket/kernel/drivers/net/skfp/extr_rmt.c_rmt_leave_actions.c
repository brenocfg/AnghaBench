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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_DISCONNECT ; 
 int /*<<< orphan*/  EVENT_ECM ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmt_leave_actions(struct s_smc *smc)
{
	queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
	/*
	 * Note: Do NOT try again later. (with please reconnect)
	 * The station must be left from the ring!
	 */
}