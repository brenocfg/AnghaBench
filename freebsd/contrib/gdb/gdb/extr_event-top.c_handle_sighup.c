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
 int /*<<< orphan*/  mark_async_signal_handler_wrapper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sighup_token ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 

__attribute__((used)) static void
handle_sighup (int sig)
{
  mark_async_signal_handler_wrapper (sighup_token);
  signal (sig, handle_sighup);
}