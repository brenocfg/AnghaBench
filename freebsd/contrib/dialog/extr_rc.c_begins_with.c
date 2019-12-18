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
 int /*<<< orphan*/  dlg_strcmp (char const*,char*) ; 
 int skip_keyword (char*,int) ; 
 int skip_whitespace (char*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
begins_with(char *line, const char *keyword, char **params)
{
    int i = skip_whitespace(line, 0);
    int j = skip_keyword(line, i);

    if ((j - i) == (int) strlen(keyword)) {
	char save = line[j];
	line[j] = 0;
	if (!dlg_strcmp(keyword, line + i)) {
	    *params = line + skip_whitespace(line, j + 1);
	    return 1;
	}
	line[j] = save;
    }

    return 0;
}