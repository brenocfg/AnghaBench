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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_int_C(const char *name, const unsigned char *buf, size_t len)
{
	size_t u;

	printf("\nstatic const unsigned char %s[] = {", name);
	for (u = 0; u < len; u ++) {
		if (u != 0) {
			printf(",");
		}
		if (u % 12 == 0) {
			printf("\n\t");
		} else {
			printf(" ");
		}
		printf("0x%02X", buf[u]);
	}
	printf("\n};\n");
}