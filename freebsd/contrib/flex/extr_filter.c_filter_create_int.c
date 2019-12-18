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
struct filter {int (* filter_func ) (struct filter*) ;struct filter* next; void* extra; int /*<<< orphan*/ * argv; scalar_t__ argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ flex_alloc (int) ; 
 int /*<<< orphan*/  flexerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct filter*,int /*<<< orphan*/ ,int) ; 

struct filter *filter_create_int (struct filter *chain,
				  int (*filter_func) (struct filter *),
				  void *extra)
{
	struct filter *f;

	/* allocate and initialize new filter */
	f = (struct filter *) flex_alloc (sizeof (struct filter));
	if (!f)
		flexerror (_("flex_alloc failed in filter_create_int"));
	memset (f, 0, sizeof (*f));
	f->next = NULL;
	f->argc = 0;
	f->argv = NULL;

	f->filter_func = filter_func;
	f->extra = extra;

	if (chain != NULL) {
		/* append f to end of chain */
		while (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	return f;
}