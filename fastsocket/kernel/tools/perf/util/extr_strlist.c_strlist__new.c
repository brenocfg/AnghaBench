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
struct TYPE_2__ {int /*<<< orphan*/  node_delete; int /*<<< orphan*/  node_new; int /*<<< orphan*/  node_cmp; } ;
struct strlist {int dupstr; TYPE_1__ rblist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct strlist*) ; 
 struct strlist* malloc (int) ; 
 int /*<<< orphan*/  rblist__init (TYPE_1__*) ; 
 int /*<<< orphan*/  strlist__node_cmp ; 
 int /*<<< orphan*/  strlist__node_delete ; 
 int /*<<< orphan*/  strlist__node_new ; 
 scalar_t__ strlist__parse_list (struct strlist*,char const*) ; 

struct strlist *strlist__new(bool dupstr, const char *slist)
{
	struct strlist *self = malloc(sizeof(*self));

	if (self != NULL) {
		rblist__init(&self->rblist);
		self->rblist.node_cmp    = strlist__node_cmp;
		self->rblist.node_new    = strlist__node_new;
		self->rblist.node_delete = strlist__node_delete;

		self->dupstr	 = dupstr;
		if (slist && strlist__parse_list(self, slist) != 0)
			goto out_error;
	}

	return self;
out_error:
	free(self);
	return NULL;
}