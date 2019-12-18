#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ count; } ;
struct func {char* name; struct caller* callers; TYPE_1__ count; struct func* link; } ;
struct file {char* name; struct func* funcs; } ;
struct caller {int count; char* name; char* file; int y; int x; struct caller* link; } ;

/* Variables and functions */
 int fcount ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void printfuncs(struct file *p, int nf) {
	struct func *q;

	if (nf)
		printf("%s:\n", p->name);
	for (q = p->funcs; q; q = q->link)
		if (fcount <= 1 || q->count.count == 0 || !q->callers)
			printf("%d\t%s\n", q->count.count, q->name);
		else {
			struct caller *r;
			for (r = q->callers; r; r = r->link)
				printf("%d\t%s\tfrom %s\tin %s:%d.%d\n", r->count, q->name, r->name,
					r->file, r->y, r->x + 1);
		}
		
}