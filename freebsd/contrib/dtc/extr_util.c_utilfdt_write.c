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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int utilfdt_write_err (char const*,void const*) ; 

int utilfdt_write(const char *filename, const void *blob)
{
	int ret = utilfdt_write_err(filename, blob);

	if (ret) {
		fprintf(stderr, "Couldn't write blob to '%s': %s\n", filename,
			strerror(ret));
	}
	return ret ? -1 : 0;
}