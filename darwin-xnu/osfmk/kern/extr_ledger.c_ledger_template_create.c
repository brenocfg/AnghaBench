#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct entry_template {int dummy; } ;
typedef  TYPE_1__* ledger_template_t ;
struct TYPE_4__ {char const* lt_name; int lt_refs; int lt_table_size; struct entry_template* lt_entries; int /*<<< orphan*/  lt_lock; int /*<<< orphan*/ * lt_zone; scalar_t__ lt_inuse; scalar_t__ lt_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_lck_grp ; 

ledger_template_t
ledger_template_create(const char *name)
{
	ledger_template_t template;

	template = (ledger_template_t)kalloc(sizeof (*template));
	if (template == NULL)
		return (NULL);

	template->lt_name = name;
	template->lt_refs = 1;
	template->lt_cnt = 0;
	template->lt_table_size = 1;
	template->lt_inuse = 0;
	template->lt_zone = NULL;
	lck_mtx_init(&template->lt_lock, &ledger_lck_grp, LCK_ATTR_NULL);

	template->lt_entries = (struct entry_template *)
	    kalloc(sizeof (struct entry_template) * template->lt_table_size);
	if (template->lt_entries == NULL) {
		kfree(template, sizeof (*template));
		template = NULL;
	}

	return (template);
}