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
typedef  int u32 ;

/* Variables and functions */
 int RHNCAPINTS ; 
 int /*<<< orphan*/  check_cpu (int*,int*,int**) ; 
 char* cpu_name (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ x86_cap_strs ; 

int validate_cpu(void)
{
	u32 *err_flags;
	int cpu_level, req_level;
	const unsigned char *msg_strs;

	check_cpu(&cpu_level, &req_level, &err_flags);

	if (cpu_level < req_level) {
		printf("This kernel requires an %s CPU, ",
		       cpu_name(req_level));
		printf("but only detected an %s CPU.\n",
		       cpu_name(cpu_level));
		return -1;
	}

	if (err_flags) {
		int i, j;
		puts("This kernel requires the following features "
		     "not present on the CPU:\n");

		msg_strs = (const unsigned char *)x86_cap_strs;

		for (i = 0; i < RHNCAPINTS; i++) {
			u32 e = err_flags[i];

			for (j = 0; j < 32; j++) {
				if (msg_strs[0] < i ||
				    (msg_strs[0] == i && msg_strs[1] < j)) {
					/* Skip to the next string */
					msg_strs += 2;
					while (*msg_strs++)
						;
				}
				if (e & 1) {
					if (msg_strs[0] == i &&
					    msg_strs[1] == j &&
					    msg_strs[2])
						printf("%s ", msg_strs+2);
					else
						printf("%d:%d ", i, j);
				}
				e >>= 1;
			}
		}
		putchar('\n');
		return -1;
	} else {
		return 0;
	}
}