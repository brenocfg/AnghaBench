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

/* Variables and functions */
 int /*<<< orphan*/  ITRC_INTR ; 
 int /*<<< orphan*/  ITRC_NO_PORT ; 
 int ITRC_RETURN ; 
 int /*<<< orphan*/  POLL_TIMEOUT ; 
 int /*<<< orphan*/  PollTimer ; 
 int /*<<< orphan*/  ip2_polled_interrupt () ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ip2_poll(unsigned long arg)
{
	ip2trace (ITRC_NO_PORT, ITRC_INTR, 100, 0 );

	// Just polled boards, IRQ = 0 will hit all non-interrupt boards.
	// It will NOT poll boards handled by hard interrupts.
	// The issue of queued BH interrupts is handled in ip2_interrupt().
	ip2_polled_interrupt();

	mod_timer(&PollTimer, POLL_TIMEOUT);

	ip2trace (ITRC_NO_PORT, ITRC_INTR, ITRC_RETURN, 0 );
}