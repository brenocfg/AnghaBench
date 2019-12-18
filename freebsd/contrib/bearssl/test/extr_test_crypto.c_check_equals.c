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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ memcmp (void const*,void const*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
check_equals(const char *banner, const void *v1, const void *v2, size_t len)
{
	size_t u;
	const unsigned char *b;

	if (memcmp(v1, v2, len) == 0) {
		return;
	}
	fprintf(stderr, "\n%s failed\n", banner);
	fprintf(stderr, "v1: ");
	for (u = 0, b = v1; u < len; u ++) {
		fprintf(stderr, "%02X", b[u]);
	}
	fprintf(stderr, "\nv2: ");
	for (u = 0, b = v2; u < len; u ++) {
		fprintf(stderr, "%02X", b[u]);
	}
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}