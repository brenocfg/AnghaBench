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
struct kinfo_proc {int dummy; } ;

/* Variables and functions */
 char* delim ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  show_process (struct kinfo_proc const*) ; 

__attribute__((used)) static int
grepact(const struct kinfo_proc *kp)
{
	static bool first = true;

	if (!quiet && !first)
		printf("%s", delim);
	show_process(kp);
	first = false;
	return (1);
}