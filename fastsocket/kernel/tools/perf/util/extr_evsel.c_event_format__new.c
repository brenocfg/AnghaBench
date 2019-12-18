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
struct event_format {int dummy; } ;

/* Variables and functions */
 scalar_t__ BUFSIZ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pevent_parse_format (struct event_format**,void*,size_t,char const*) ; 
 int read (int,void*,scalar_t__) ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/  tracing_events_path ; 

struct event_format *event_format__new(const char *sys, const char *name)
{
	int fd, n;
	char *filename;
	void *bf = NULL, *nbf;
	size_t size = 0, alloc_size = 0;
	struct event_format *format = NULL;

	if (asprintf(&filename, "%s/%s/%s/format", tracing_events_path, sys, name) < 0)
		goto out;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		goto out_free_filename;

	do {
		if (size == alloc_size) {
			alloc_size += BUFSIZ;
			nbf = realloc(bf, alloc_size);
			if (nbf == NULL)
				goto out_free_bf;
			bf = nbf;
		}

		n = read(fd, bf + size, BUFSIZ);
		if (n < 0)
			goto out_free_bf;
		size += n;
	} while (n > 0);

	pevent_parse_format(&format, bf, size, sys);

out_free_bf:
	free(bf);
	close(fd);
out_free_filename:
	free(filename);
out:
	return format;
}