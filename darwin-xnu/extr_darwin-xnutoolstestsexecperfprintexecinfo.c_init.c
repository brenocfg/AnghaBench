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
 int strlen (char const*) ; 

__attribute__((constructor))
void init(int argc, const char *argv[], const char *envp[], const char *appl[], void *vars __attribute__((unused))) {
	int i;

	printf("argv = %p\n", argv);
	for (i=0; argv[i]; i++) {
		printf("argv[%2d] = %p %.100s%s\n", i, argv[i], argv[i], strlen(argv[i]) > 100 ? "..." : "");
	}
	printf("envp = %p\n", envp);
	for (i=0; envp[i]; i++) {
		printf("envp[%2d] = %p %.100s%s\n", i, envp[i], envp[i], strlen(envp[i]) > 100 ? "..." : "");
	}
	printf("appl = %p\n", appl);
	for (i=0; appl[i]; i++) {
		printf("appl[%2d] = %p %.100s%s\n", i, appl[i], appl[i], strlen(appl[i]) > 100 ? "..." : "");
	}
}