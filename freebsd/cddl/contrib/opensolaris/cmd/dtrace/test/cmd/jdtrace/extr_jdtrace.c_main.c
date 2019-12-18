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
 char** alloca (int) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
main(int argc, char **argv)
{
	int i, ac, has64;
	char **av, **p;

	ac = argc + 3;
	av = p = alloca(sizeof (char *) * ac);

	*p++ = "java";
	*p++ = "-jar";
	*p++ = "/opt/SUNWdtrt/lib/java/jdtrace.jar";

	argc--;
	argv++;

	for (i = 0; i < argc; i++) {
		p[i] = argv[i];
	}
	p[i] = NULL;

	(void) execvp(av[0], av);

	perror("exec failed");

	return (0);
}