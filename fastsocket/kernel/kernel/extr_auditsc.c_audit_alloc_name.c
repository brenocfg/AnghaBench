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
struct audit_names {int should_free; unsigned long ino; unsigned char type; int /*<<< orphan*/  list; } ;
struct audit_context {size_t name_count; int /*<<< orphan*/  ino_count; int /*<<< orphan*/  names_list; struct audit_names* preallocated_names; } ;

/* Variables and functions */
 size_t AUDIT_NAMES ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct audit_names* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct audit_names*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct audit_names *audit_alloc_name(struct audit_context *context,
						unsigned char type)
{
	struct audit_names *aname;

	if (context->name_count < AUDIT_NAMES) {
		aname = &context->preallocated_names[context->name_count];
		memset(aname, 0, sizeof(*aname));
	} else {
		aname = kzalloc(sizeof(*aname), GFP_NOFS);
		if (!aname)
			return NULL;
		aname->should_free = true;
	}

	aname->ino = (unsigned long)-1;
	aname->type = type;
	list_add_tail(&aname->list, &context->names_list);

	context->name_count++;
#if AUDIT_DEBUG
	context->ino_count++;
#endif
	return aname;
}