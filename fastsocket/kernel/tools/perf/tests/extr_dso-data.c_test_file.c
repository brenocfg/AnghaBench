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
 int /*<<< orphan*/  close (int) ; 
 unsigned char* malloc (int) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int write (int,unsigned char*,int) ; 

__attribute__((used)) static char *test_file(int size)
{
	static char buf_templ[] = "/tmp/test-XXXXXX";
	char *templ = buf_templ;
	int fd, i;
	unsigned char *buf;

	fd = mkstemp(templ);
	if (fd < 0) {
		perror("mkstemp failed");
		return NULL;
	}

	buf = malloc(size);
	if (!buf) {
		close(fd);
		return NULL;
	}

	for (i = 0; i < size; i++)
		buf[i] = (unsigned char) ((int) i % 10);

	if (size != write(fd, buf, size))
		templ = NULL;

	close(fd);
	return templ;
}