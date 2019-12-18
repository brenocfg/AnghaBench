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
 int /*<<< orphan*/  async_remote_interrupt_twice ; 
 int /*<<< orphan*/  create_async_signal_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_remote_sigint_twice ; 
 int /*<<< orphan*/  mark_async_signal_handler_wrapper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigint_remote_token ; 
 int /*<<< orphan*/  sigint_remote_twice_token ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_remote_sigint (int sig)
{
  signal (sig, handle_remote_sigint_twice);
  sigint_remote_twice_token =
    create_async_signal_handler (async_remote_interrupt_twice, NULL);
  mark_async_signal_handler_wrapper (sigint_remote_token);
}