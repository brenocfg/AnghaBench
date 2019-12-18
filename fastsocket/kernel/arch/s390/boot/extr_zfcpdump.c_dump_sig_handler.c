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
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  __sighandler_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERR (char*,...) ; 
 int /*<<< orphan*/  terminate () ; 

__attribute__((used)) static __sighandler_t dump_sig_handler(int sig, siginfo_t *sip, void*p)
{
	PRINT_ERR("Got signal: %i\n", sig);
	PRINT_ERR("Dump failed!\n");
	terminate();
	return 0;
}