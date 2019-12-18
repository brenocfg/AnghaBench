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
struct list_head {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line_list__add_line (struct list_head*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ strlazymatch (char*,char const*) ; 

__attribute__((used)) static int find_lazy_match_lines(struct list_head *head,
				 const char *fname, const char *pat)
{
	FILE *fp;
	char *line = NULL;
	size_t line_len;
	ssize_t len;
	int count = 0, linenum = 1;

	fp = fopen(fname, "r");
	if (!fp) {
		pr_warning("Failed to open %s: %s\n", fname, strerror(errno));
		return -errno;
	}

	while ((len = getline(&line, &line_len, fp)) > 0) {

		if (line[len - 1] == '\n')
			line[len - 1] = '\0';

		if (strlazymatch(line, pat)) {
			line_list__add_line(head, linenum);
			count++;
		}
		linenum++;
	}

	if (ferror(fp))
		count = -errno;
	free(line);
	fclose(fp);

	if (count == 0)
		pr_debug("No matched lines found in %s.\n", fname);
	return count;
}