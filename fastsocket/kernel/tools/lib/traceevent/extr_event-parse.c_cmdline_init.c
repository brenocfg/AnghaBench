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
struct pevent {int cmdline_count; struct cmdline_list* cmdlist; struct cmdline* cmdlines; } ;
struct cmdline_list {struct cmdline_list* next; int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;
struct cmdline {int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdline_cmp ; 
 int /*<<< orphan*/  free (struct cmdline_list*) ; 
 struct cmdline* malloc (int) ; 
 int /*<<< orphan*/  qsort (struct cmdline*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmdline_init(struct pevent *pevent)
{
	struct cmdline_list *cmdlist = pevent->cmdlist;
	struct cmdline_list *item;
	struct cmdline *cmdlines;
	int i;

	cmdlines = malloc(sizeof(*cmdlines) * pevent->cmdline_count);
	if (!cmdlines)
		return -1;

	i = 0;
	while (cmdlist) {
		cmdlines[i].pid = cmdlist->pid;
		cmdlines[i].comm = cmdlist->comm;
		i++;
		item = cmdlist;
		cmdlist = cmdlist->next;
		free(item);
	}

	qsort(cmdlines, pevent->cmdline_count, sizeof(*cmdlines), cmdline_cmp);

	pevent->cmdlines = cmdlines;
	pevent->cmdlist = NULL;

	return 0;
}