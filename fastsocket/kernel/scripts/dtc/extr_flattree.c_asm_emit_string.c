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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void asm_emit_string(void *e, char *str, int len)
{
	FILE *f = e;
	char c = 0;

	if (len != 0) {
		/* XXX: ewww */
		c = str[len];
		str[len] = '\0';
	}

	fprintf(f, "\t.string\t\"%s\"\n", str);

	if (len != 0) {
		str[len] = c;
	}
}