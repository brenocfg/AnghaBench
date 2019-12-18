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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 

int access(const char* path, int mode) {
	return 0; /* TODO temp hack, real code below */

	FILE* fd = fopen(path, "rb");
	if (fd < 0) {
		fclose(fd);
		/* We're supposed to set errono here */
		return -1;
	} else {
		fclose(fd);
		return 0;
	}
}