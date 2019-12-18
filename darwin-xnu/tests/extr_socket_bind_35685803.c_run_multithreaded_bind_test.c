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
 int /*<<< orphan*/  T_PASS (char*,char*) ; 
 int /*<<< orphan*/  multithreaded_bind_test (int,int) ; 

__attribute__((used)) static void
run_multithreaded_bind_test(int number_of_runs, bool v6, int socket_count)
{
	for (int i = 0; i < number_of_runs; i++) {
		multithreaded_bind_test(v6, socket_count);
	}
	T_PASS("multithreaded_bind_test %s", v6 ? "IPv6" : "IPv4");
}