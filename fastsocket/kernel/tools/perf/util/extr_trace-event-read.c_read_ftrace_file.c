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
struct pevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc_or_die (unsigned long long) ; 
 int /*<<< orphan*/  parse_ftrace_file (struct pevent*,char*,unsigned long long) ; 
 int /*<<< orphan*/  read_or_die (char*,unsigned long long) ; 

__attribute__((used)) static void read_ftrace_file(struct pevent *pevent, unsigned long long size)
{
	char *buf;

	buf = malloc_or_die(size);
	read_or_die(buf, size);
	parse_ftrace_file(pevent, buf, size);
	free(buf);
}