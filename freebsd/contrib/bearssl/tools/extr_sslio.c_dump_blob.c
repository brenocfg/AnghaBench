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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
dump_blob(const char *name, const void *data, size_t len)
{
	const unsigned char *buf;
	size_t u;

	buf = data;
	fprintf(stderr, "%s (len = %lu)", name, (unsigned long)len);
	for (u = 0; u < len; u ++) {
		if ((u & 15) == 0) {
			fprintf(stderr, "\n%08lX  ", (unsigned long)u);
		} else if ((u & 7) == 0) {
			fprintf(stderr, " ");
		}
		fprintf(stderr, " %02x", buf[u]);
	}
	fprintf(stderr, "\n");
}