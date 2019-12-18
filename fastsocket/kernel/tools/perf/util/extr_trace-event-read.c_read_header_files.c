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
 int BUFSIZ ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  header_page_size_size ; 
 int /*<<< orphan*/  long_size ; 
 char* malloc_or_die (unsigned long long) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 unsigned long long read8 (struct pevent*) ; 
 int /*<<< orphan*/  read_or_die (char*,unsigned long long) ; 
 int /*<<< orphan*/  skip (unsigned long long) ; 

__attribute__((used)) static void read_header_files(struct pevent *pevent)
{
	unsigned long long size;
	char *header_event;
	char buf[BUFSIZ];

	read_or_die(buf, 12);

	if (memcmp(buf, "header_page", 12) != 0)
		die("did not read header page");

	size = read8(pevent);
	skip(size);

	/*
	 * The size field in the page is of type long,
	 * use that instead, since it represents the kernel.
	 */
	long_size = header_page_size_size;

	read_or_die(buf, 13);
	if (memcmp(buf, "header_event", 13) != 0)
		die("did not read header event");

	size = read8(pevent);
	header_event = malloc_or_die(size);
	read_or_die(header_event, size);
	free(header_event);
}