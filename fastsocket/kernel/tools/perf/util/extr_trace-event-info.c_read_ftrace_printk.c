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
 char* get_tracing_file (char*) ; 
 int /*<<< orphan*/  put_tracing_file (char*) ; 
 int /*<<< orphan*/  record_file (char*,int) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  write_or_die (unsigned int*,int) ; 

__attribute__((used)) static void read_ftrace_printk(void)
{
	unsigned int size;
	char *path;
	struct stat st;
	int ret;

	path = get_tracing_file("printk_formats");
	ret = stat(path, &st);
	if (ret < 0) {
		/* not found */
		size = 0;
		write_or_die(&size, 4);
		goto out;
	}
	record_file(path, 4);

out:
	put_tracing_file(path);
}