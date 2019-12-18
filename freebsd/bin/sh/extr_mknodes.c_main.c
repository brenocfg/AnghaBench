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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* line ; 
 int /*<<< orphan*/  output (char*) ; 
 int /*<<< orphan*/  parsefield () ; 
 int /*<<< orphan*/  parsenode () ; 
 scalar_t__ readline (int /*<<< orphan*/ *) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	FILE *infp;

	if (argc != 3)
		error("usage: mknodes file");
	if ((infp = fopen(argv[1], "r")) == NULL)
		error("Can't open %s: %s", argv[1], strerror(errno));
	while (readline(infp)) {
		if (line[0] == ' ' || line[0] == '\t')
			parsefield();
		else if (line[0] != '\0')
			parsenode();
	}
	fclose(infp);
	output(argv[2]);
	exit(0);
}