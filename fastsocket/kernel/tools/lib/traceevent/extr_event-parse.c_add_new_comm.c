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
struct pevent {int cmdline_count; struct cmdline* cmdlines; } ;
struct cmdline {int pid; scalar_t__ comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cmdline* bsearch (struct cmdline*,struct cmdline*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdline_cmp ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct cmdline*) ; 
 int /*<<< orphan*/  qsort (struct cmdline*,size_t,int,int /*<<< orphan*/ ) ; 
 struct cmdline* realloc (struct cmdline*,int) ; 
 scalar_t__ strdup (char const*) ; 

__attribute__((used)) static int add_new_comm(struct pevent *pevent, const char *comm, int pid)
{
	struct cmdline *cmdlines = pevent->cmdlines;
	const struct cmdline *cmdline;
	struct cmdline key;

	if (!pid)
		return 0;

	/* avoid duplicates */
	key.pid = pid;

	cmdline = bsearch(&key, pevent->cmdlines, pevent->cmdline_count,
		       sizeof(*pevent->cmdlines), cmdline_cmp);
	if (cmdline) {
		errno = EEXIST;
		return -1;
	}

	cmdlines = realloc(cmdlines, sizeof(*cmdlines) * (pevent->cmdline_count + 1));
	if (!cmdlines) {
		errno = ENOMEM;
		return -1;
	}

	cmdlines[pevent->cmdline_count].comm = strdup(comm);
	if (!cmdlines[pevent->cmdline_count].comm) {
		free(cmdlines);
		errno = ENOMEM;
		return -1;
	}

	cmdlines[pevent->cmdline_count].pid = pid;
		
	if (cmdlines[pevent->cmdline_count].comm)
		pevent->cmdline_count++;

	qsort(cmdlines, pevent->cmdline_count, sizeof(*cmdlines), cmdline_cmp);
	pevent->cmdlines = cmdlines;

	return 0;
}