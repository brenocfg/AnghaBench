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
struct dso {scalar_t__* dynv; scalar_t__ strings; char* name; struct dso* next; struct dso** deps; } ;

/* Variables and functions */
 scalar_t__ DT_NEEDED ; 
 int /*<<< orphan*/  error (char*,scalar_t__,char*) ; 
 struct dso* load_library (scalar_t__,struct dso*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 struct dso** realloc (struct dso**,int) ; 
 int /*<<< orphan*/ * rtld_fail ; 
 scalar_t__ runtime ; 

__attribute__((used)) static void load_deps(struct dso *p)
{
	size_t i, ndeps=0;
	struct dso ***deps = &p->deps, **tmp, *dep;
	for (; p; p=p->next) {
		for (i=0; p->dynv[i]; i+=2) {
			if (p->dynv[i] != DT_NEEDED) continue;
			dep = load_library(p->strings + p->dynv[i+1], p);
			if (!dep) {
				error("Error loading shared library %s: %m (needed by %s)",
					p->strings + p->dynv[i+1], p->name);
				if (runtime) longjmp(*rtld_fail, 1);
				continue;
			}
			if (runtime) {
				tmp = realloc(*deps, sizeof(*tmp)*(ndeps+2));
				if (!tmp) longjmp(*rtld_fail, 1);
				tmp[ndeps++] = dep;
				tmp[ndeps] = 0;
				*deps = tmp;
			}
		}
	}
}