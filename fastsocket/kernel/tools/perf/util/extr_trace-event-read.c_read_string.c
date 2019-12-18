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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ calc_data_size ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  input_fd ; 
 char* malloc_or_die (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ repipe ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *read_string(void)
{
	char buf[BUFSIZ];
	char *str = NULL;
	int size = 0;
	off_t r;
	char c;

	for (;;) {
		r = read(input_fd, &c, 1);
		if (r < 0)
			die("reading input file");

		if (!r)
			die("no data");

		if (repipe) {
			int retw = write(STDOUT_FILENO, &c, 1);

			if (retw <= 0 || retw != r)
				die("repiping input file string");
		}

		buf[size++] = c;

		if (!c)
			break;
	}

	if (calc_data_size)
		calc_data_size += size;

	str = malloc_or_die(size);
	memcpy(str, buf, size);

	return str;
}