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
struct sigaction {scalar_t__ sa_handler; } ;

/* Variables and functions */
 scalar_t__ SIG_IGN ; 
 int sigaction (int,struct sigaction const*,struct sigaction*) ; 

__attribute__((used)) static int
setup_sig(int sig, const struct sigaction *n_hand)
{
	struct sigaction o_hand;

	if (sigaction(sig, NULL, &o_hand) < 0)
		return (-1);

	if (o_hand.sa_handler == SIG_IGN)
		return (0);

	return (sigaction(sig, n_hand, NULL));
}