#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_6__ {TYPE_3__* map; } ;
struct hist_entry {TYPE_1__ pairs; int /*<<< orphan*/  callchain; TYPE_2__ ms; } ;
struct callchain_root {int dummy; } ;
struct TYPE_8__ {scalar_t__ use_callchain; } ;
struct TYPE_7__ {int referenced; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callchain_init (int /*<<< orphan*/ ) ; 
 struct hist_entry* malloc (int) ; 
 TYPE_4__ symbol_conf ; 

__attribute__((used)) static struct hist_entry *hist_entry__new(struct hist_entry *template)
{
	size_t callchain_size = symbol_conf.use_callchain ? sizeof(struct callchain_root) : 0;
	struct hist_entry *he = malloc(sizeof(*he) + callchain_size);

	if (he != NULL) {
		*he = *template;

		if (he->ms.map)
			he->ms.map->referenced = true;
		if (symbol_conf.use_callchain)
			callchain_init(he->callchain);

		INIT_LIST_HEAD(&he->pairs.node);
	}

	return he;
}