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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static int seek_sect(FILE *f, const char *section)
{
	char line[128], *tmp;
	int len;

	len = strlen(section);
	// seek to the section needed
	while (!feof(f))
	{
		tmp = fgets(line, sizeof(line), f);
		if (tmp == NULL) break;

		if (line[0] != '[') continue; // not section start
		if (strncmp(line + 1, section, len) == 0 && line[len+1] == ']')
			return 1; // found it
	}

	return 0;
}