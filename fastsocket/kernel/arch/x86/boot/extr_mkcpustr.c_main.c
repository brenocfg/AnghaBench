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
 int RHNCAPINTS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** x86_cap_flags ; 

int main(void)
{
	int i, j;
	const char *str;

	printf("static const char x86_cap_strs[] =\n");

	for (i = 0; i < RHNCAPINTS; i++) {
		for (j = 0; j < 32; j++) {
			str = x86_cap_flags[i*32+j];

			if (i == RHNCAPINTS-1 && j == 31) {
				/* The last entry must be unconditional; this
				   also consumes the compiler-added null
				   character */
				if (!str)
					str = "";
				printf("\t\"\\x%02x\\x%02x\"\"%s\"\n",
				       i, j, str);
			} else if (str) {
				printf("#if REQUIRED_MASK%d & (1 << %d)\n"
				       "\t\"\\x%02x\\x%02x\"\"%s\\0\"\n"
				       "#endif\n",
				       i, j, i, j, str);
			}
		}
	}
	printf("\t;\n");
	return 0;
}