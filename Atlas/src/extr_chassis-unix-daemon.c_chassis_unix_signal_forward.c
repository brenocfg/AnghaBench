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
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chassis_unix_signal_forward(int sig) {
#ifdef _WIN32
	g_assert_not_reached(); /* shouldn't be tried to be called on win32 */
#else
	signal(sig, SIG_IGN); /* we don't want to create a loop here */

	kill(0, sig);
#endif
}