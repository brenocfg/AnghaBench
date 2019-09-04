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
 int /*<<< orphan*/  exit (int) ; 
 int received_nb_signals ; 
 int received_sigterm ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  term_exit_sigsafe () ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sigterm_handler(int sig)
{
    int ret;
    received_sigterm = sig;
    received_nb_signals++;
    term_exit_sigsafe();
    if(received_nb_signals > 3) {
        ret = write(2/*STDERR_FILENO*/, "Received > 3 system signals, hard exiting\n",
                    strlen("Received > 3 system signals, hard exiting\n"));
        if (ret < 0) { /* Do nothing */ };
        exit(123);
    }
}