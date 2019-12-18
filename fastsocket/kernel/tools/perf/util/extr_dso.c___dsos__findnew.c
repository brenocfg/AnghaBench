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
 struct dso* dso__new (char const*) ; 
 int /*<<< orphan*/  dso__set_basename (struct dso*) ; 
 int /*<<< orphan*/  dsos__add (struct list_head*,struct dso*) ; 
 struct dso* dsos__find (struct list_head*,char const*) ; 

struct dso *__dsos__findnew(struct list_head *head, const char *name)
{
	struct dso *dso = dsos__find(head, name);

	if (!dso) {
		dso = dso__new(name);
		if (dso != NULL) {
			dsos__add(head, dso);
			dso__set_basename(dso);
		}
	}

	return dso;
}