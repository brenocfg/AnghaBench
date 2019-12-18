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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void print_kvm_stat_usage(void)
{
	printf("Usage: perf kvm stat <command>\n\n");

	printf("# Available commands:\n");
	printf("\trecord: record kvm events\n");
	printf("\treport: report statistical data of kvm events\n");

	printf("\nOtherwise, it is the alias of 'perf stat':\n");
}