#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ledger_template_t ;
struct TYPE_7__ {int lt_cnt; TYPE_1__* lt_entries; } ;
struct TYPE_6__ {int /*<<< orphan*/  et_key; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  template_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  template_unlock (TYPE_2__*) ; 

int
ledger_key_lookup(ledger_template_t template, const char *key)
{
	int idx;

	template_lock(template);
	for (idx = 0; idx < template->lt_cnt; idx++)
		if (template->lt_entries != NULL &&
		    (strcmp(key, template->lt_entries[idx].et_key) == 0))
			break;

	if (idx >= template->lt_cnt)
		idx = -1;
	template_unlock(template);

	return (idx);
}