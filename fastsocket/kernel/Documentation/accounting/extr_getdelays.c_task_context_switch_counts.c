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
struct taskstats {scalar_t__ nivcsw; scalar_t__ nvcsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*,unsigned long long,unsigned long long) ; 

__attribute__((used)) static void task_context_switch_counts(struct taskstats *t)
{
	printf("\n\nTask   %15s%15s\n"
	       "       %15llu%15llu\n",
	       "voluntary", "nonvoluntary",
	       (unsigned long long)t->nvcsw, (unsigned long long)t->nivcsw);
}