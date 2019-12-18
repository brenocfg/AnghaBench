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
struct strlist {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_CMDLEN ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int strlen (char*) ; 
 int strlist__add (struct strlist*,char*) ; 
 int /*<<< orphan*/  strlist__delete (struct strlist*) ; 
 struct strlist* strlist__new (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct strlist *get_probe_trace_command_rawlist(int fd)
{
	int ret, idx;
	FILE *fp;
	char buf[MAX_CMDLEN];
	char *p;
	struct strlist *sl;

	sl = strlist__new(true, NULL);

	fp = fdopen(dup(fd), "r");
	while (!feof(fp)) {
		p = fgets(buf, MAX_CMDLEN, fp);
		if (!p)
			break;

		idx = strlen(p) - 1;
		if (p[idx] == '\n')
			p[idx] = '\0';
		ret = strlist__add(sl, buf);
		if (ret < 0) {
			pr_debug("strlist__add failed: %s\n", strerror(-ret));
			strlist__delete(sl);
			return NULL;
		}
	}
	fclose(fp);

	return sl;
}