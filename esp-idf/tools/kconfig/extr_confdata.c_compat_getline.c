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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  EOF 128 
 int /*<<< orphan*/  add_byte (int,char**,size_t,size_t*) ; 
 int getc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t compat_getline(char **lineptr, size_t *n, FILE *stream)
{
	char *line = *lineptr;
	size_t slen = 0;

	for (;;) {
		int c = getc(stream);

		switch (c) {
		case '\n':
			if (add_byte(c, &line, slen, n) < 0)
				goto e_out;
			slen++;
			/* fall through */
		case EOF:
			if (add_byte('\0', &line, slen, n) < 0)
				goto e_out;
			*lineptr = line;
			if (slen == 0)
				return -1;
			return slen;
		default:
			if (add_byte(c, &line, slen, n) < 0)
				goto e_out;
			slen++;
		}
	}

e_out:
	line[slen-1] = '\0';
	*lineptr = line;
	return -1;
}