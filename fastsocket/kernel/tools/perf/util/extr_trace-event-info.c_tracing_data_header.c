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
 char* VERSION ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 scalar_t__ bigendian () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char page_size ; 
 int /*<<< orphan*/  read_trace_init (char,char) ; 
 int strlen (char*) ; 
 char sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_or_die (char*,int) ; 

__attribute__((used)) static void tracing_data_header(void)
{
	char buf[20];

	/* just guessing this is someone's birthday.. ;) */
	buf[0] = 23;
	buf[1] = 8;
	buf[2] = 68;
	memcpy(buf + 3, "tracing", 7);

	write_or_die(buf, 10);

	write_or_die(VERSION, strlen(VERSION) + 1);

	/* save endian */
	if (bigendian())
		buf[0] = 1;
	else
		buf[0] = 0;

	read_trace_init(buf[0], buf[0]);

	write_or_die(buf, 1);

	/* save size of long */
	buf[0] = sizeof(long);
	write_or_die(buf, 1);

	/* save page_size */
	page_size = sysconf(_SC_PAGESIZE);
	write_or_die(&page_size, 4);
}