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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  record_file (char const*,int) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  write_or_die (unsigned int*,int) ; 

__attribute__((used)) static void read_proc_kallsyms(void)
{
	unsigned int size;
	const char *path = "/proc/kallsyms";
	struct stat st;
	int ret;

	ret = stat(path, &st);
	if (ret < 0) {
		/* not found */
		size = 0;
		write_or_die(&size, 4);
		return;
	}
	record_file(path, 4);
}