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
 int MAXLINESZ ; 
 int /*<<< orphan*/  defaultline (char*) ; 
 int /*<<< orphan*/  docsection (char*,char*) ; 
 int /*<<< orphan*/  externalfunctions (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  internalfunctions (char*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  singlefunctions (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  symbolsonly (char*) ; 

__attribute__((used)) static void parse_file(FILE *infile)
{
	char line[MAXLINESZ];
	char * s;
	while (fgets(line, MAXLINESZ, infile)) {
		if (line[0] == '!') {
			s = line + 2;
			switch (line[1]) {
				case 'E':
					while (*s && !isspace(*s)) s++;
					*s = '\0';
					externalfunctions(line+2);
					break;
				case 'I':
					while (*s && !isspace(*s)) s++;
					*s = '\0';
					internalfunctions(line+2);
					break;
				case 'D':
					while (*s && !isspace(*s)) s++;
                                        *s = '\0';
                                        symbolsonly(line+2);
                                        break;
				case 'F':
					/* filename */
					while (*s && !isspace(*s)) s++;
					*s++ = '\0';
                                        /* function names */
					while (isspace(*s))
						s++;
					singlefunctions(line +2, s);
					break;
				case 'P':
					/* filename */
					while (*s && !isspace(*s)) s++;
					*s++ = '\0';
					/* DOC: section name */
					while (isspace(*s))
						s++;
					docsection(line + 2, s);
					break;
				default:
					defaultline(line);
			}
		}
		else {
			defaultline(line);
		}
	}
	fflush(stdout);
}