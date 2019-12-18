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
 scalar_t__ find_vdso_map (void**,void**) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* memdup (void*,size_t) ; 
 int mkstemp (char*) ; 
 char* vdso_file ; 
 int vdso_found ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static char *get_file(void)
{
	char *vdso = NULL;
	char *buf = NULL;
	void *start, *end;
	size_t size;
	int fd;

	if (vdso_found)
		return vdso_file;

	if (find_vdso_map(&start, &end))
		return NULL;

	size = end - start;

	buf = memdup(start, size);
	if (!buf)
		return NULL;

	fd = mkstemp(vdso_file);
	if (fd < 0)
		goto out;

	if (size == (size_t) write(fd, buf, size))
		vdso = vdso_file;

	close(fd);

 out:
	free(buf);

	vdso_found = (vdso != NULL);
	return vdso;
}