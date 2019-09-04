#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct match {char* name; struct match* next; } ;
struct TYPE_3__ {size_t gl_offs; size_t gl_pathc; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int GLOB_APPEND ; 
 int GLOB_DOOFFS ; 
 int GLOB_NOCHECK ; 
 int GLOB_NOMATCH ; 
 int GLOB_NOSORT ; 
 int GLOB_NOSPACE ; 
 scalar_t__ PATH_MAX ; 
 scalar_t__ append (struct match**,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freelist (struct match*) ; 
 int ignore_err (char const*,int) ; 
 char** malloc (size_t) ; 
 int match_in_dir (char const*,char const*,int,int (*) (char const*,int),struct match**) ; 
 int /*<<< orphan*/  qsort (char**,size_t,int,int /*<<< orphan*/ ) ; 
 char** realloc (char**,size_t) ; 
 int /*<<< orphan*/  sort ; 
 scalar_t__ strlen (char const*) ; 

int glob(const char *restrict pat, int flags, int (*errfunc)(const char *path, int err), glob_t *restrict g)
{
	const char *p=pat, *d;
	struct match head = { .next = NULL }, *tail = &head;
	size_t cnt, i;
	size_t offs = (flags & GLOB_DOOFFS) ? g->gl_offs : 0;
	int error = 0;
	
	if (*p == '/') {
		for (; *p == '/'; p++);
		d = "/";
	} else {
		d = "";
	}

	if (strlen(p) > PATH_MAX) return GLOB_NOSPACE;

	if (!errfunc) errfunc = ignore_err;

	if (!(flags & GLOB_APPEND)) {
		g->gl_offs = offs;
		g->gl_pathc = 0;
		g->gl_pathv = NULL;
	}

	if (*p) error = match_in_dir(d, p, flags, errfunc, &tail);
	if (error == GLOB_NOSPACE) {
		freelist(&head);
		return error;
	}
	
	for (cnt=0, tail=head.next; tail; tail=tail->next, cnt++);
	if (!cnt) {
		if (flags & GLOB_NOCHECK) {
			tail = &head;
			if (append(&tail, pat, strlen(pat), 0))
				return GLOB_NOSPACE;
			cnt++;
		} else
			return GLOB_NOMATCH;
	}

	if (flags & GLOB_APPEND) {
		char **pathv = realloc(g->gl_pathv, (offs + g->gl_pathc + cnt + 1) * sizeof(char *));
		if (!pathv) {
			freelist(&head);
			return GLOB_NOSPACE;
		}
		g->gl_pathv = pathv;
		offs += g->gl_pathc;
	} else {
		g->gl_pathv = malloc((offs + cnt + 1) * sizeof(char *));
		if (!g->gl_pathv) {
			freelist(&head);
			return GLOB_NOSPACE;
		}
		for (i=0; i<offs; i++)
			g->gl_pathv[i] = NULL;
	}
	for (i=0, tail=head.next; i<cnt; tail=tail->next, i++)
		g->gl_pathv[offs + i] = tail->name;
	g->gl_pathv[offs + i] = NULL;
	g->gl_pathc += cnt;

	if (!(flags & GLOB_NOSORT))
		qsort(g->gl_pathv+offs, cnt, sizeof(char *), sort);
	
	return error;
}