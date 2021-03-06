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
 int /*<<< orphan*/  SIG_DFL ; 
 int exit_signal_received ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void signal_handler(int sig)
{
    signal(sig, SIG_DFL);
    exit_signal_received = 1;
}