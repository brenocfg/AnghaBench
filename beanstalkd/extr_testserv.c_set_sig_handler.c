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
struct sigaction {int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exit_process ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 int sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twarn (char*) ; 

__attribute__((used)) static void
set_sig_handler()
{
    struct sigaction sa;

    sa.sa_flags = 0;
    int r = sigemptyset(&sa.sa_mask);
    if (r == -1) {
        twarn("sigemptyset()");
        exit(111);
    }

    // This is required to trigger gcov on exit. See issue #443.
    sa.sa_handler = exit_process;
    r = sigaction(SIGTERM, &sa, 0);
    if (r == -1) {
        twarn("sigaction(SIGTERM)");
        exit(111);
    }
}