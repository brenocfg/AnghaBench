#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; int x; int y; } ;
struct func {char* name; TYPE_1__ count; struct caller* callers; struct func* link; } ;
struct file {char* name; int count; TYPE_2__* counts; struct func* funcs; struct file* link; } ;
struct caller {int count; char* name; char* file; int x; int y; struct caller* link; } ;
struct TYPE_4__ {int x; int y; int count; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 struct file* filelist ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

void emitdata(char *file) {
	FILE *fp;

	if (fp = fopen(file, "w")) {
		struct file *p;
		for (p = filelist; p; p = p->link) {
			int i;
			struct func *q;
			struct caller *r;
			fprintf(fp, "1\n%s\n", p->name);
			for (i = 0, q = p->funcs; q; i++, q = q->link)
				if (r = q->callers)
					for (i--; r; r = r->link)
						i++;
			fprintf(fp, "%d\n", i);
			for (q = p->funcs; q; q = q->link)
				if (q->count.count == 0 || !q->callers)
					fprintf(fp, "%s 1 %d %d %d ? ? 0 0\n", q->name, q->count.x,
						q->count.y, q->count.count);
				else
					for (r = q->callers; r; r = r->link)
						fprintf(fp, "%s 1 %d %d %d %s %s %d %d\n", q->name, q->count.x,
							q->count.y, r->count, r->name, r->file, r->x, r->y);
			fprintf(fp, "%d\n", p->count);
			for (i = 0; i < p->count; i++)
				fprintf(fp, "1 %d %d %d\n", p->counts[i].x,
					p->counts[i].y, p->counts[i].count);
		}
		fclose(fp);
	} else
		fprintf(stderr, "%s: can't create `%s'\n", progname, file);
}