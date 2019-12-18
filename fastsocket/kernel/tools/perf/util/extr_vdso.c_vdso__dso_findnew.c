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
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDSO__MAP_NAME ; 
 struct dso* dso__new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__set_long_name (struct dso*,char*) ; 
 int /*<<< orphan*/  dsos__add (struct list_head*,struct dso*) ; 
 struct dso* dsos__find (struct list_head*,int /*<<< orphan*/ ) ; 
 char* get_file () ; 

struct dso *vdso__dso_findnew(struct list_head *head)
{
	struct dso *dso = dsos__find(head, VDSO__MAP_NAME);

	if (!dso) {
		char *file;

		file = get_file();
		if (!file)
			return NULL;

		dso = dso__new(VDSO__MAP_NAME);
		if (dso != NULL) {
			dsos__add(head, dso);
			dso__set_long_name(dso, file);
		}
	}

	return dso;
}