#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ le_last_refill; scalar_t__ le_refill_period; } ;
struct TYPE_13__ {TYPE_1__ le_refill; } ;
struct ledger_entry {TYPE_2__ _le; void* le_warn_level; void* le_limit; scalar_t__ le_debit; scalar_t__ le_credit; int /*<<< orphan*/  le_flags; } ;
struct entry_template {int /*<<< orphan*/ * et_callback; int /*<<< orphan*/  et_flags; } ;
typedef  TYPE_3__* ledger_template_t ;
typedef  TYPE_4__* ledger_t ;
typedef  int int32_t ;
struct TYPE_15__ {int l_refs; int l_size; struct ledger_entry* l_entries; scalar_t__ l_id; TYPE_3__* l_template; } ;
struct TYPE_14__ {size_t lt_cnt; struct entry_template* lt_entries; scalar_t__ lt_zone; int /*<<< orphan*/  lt_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEDGER_ACTION_CALLBACK ; 
 int LEDGER_CREATE_INACTIVE_ENTRIES ; 
 void* LEDGER_LIMIT_INFINITY ; 
 TYPE_4__* LEDGER_NULL ; 
 int /*<<< orphan*/  LF_ENTRY_ACTIVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  flag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_cnt ; 
 int /*<<< orphan*/  ledger_template_dereference (TYPE_3__*) ; 
 TYPE_4__* pmap_ledger_alloc () ; 
 int /*<<< orphan*/  template_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  template_unlock (TYPE_3__*) ; 
 scalar_t__ zalloc (scalar_t__) ; 

ledger_t
ledger_instantiate(ledger_template_t template, int entry_type)
{
	ledger_t ledger;
	size_t cnt;
	int i;

	template_lock(template);
	template->lt_refs++;
	cnt = template->lt_cnt;
	template_unlock(template);

	if (template->lt_zone) {
		ledger = (ledger_t)zalloc(template->lt_zone);
	} else {
		ledger = pmap_ledger_alloc();
	}

	if (ledger == NULL) {
		ledger_template_dereference(template);
		return LEDGER_NULL;
	}

	ledger->l_template = template;
	ledger->l_id = ledger_cnt++;
	ledger->l_refs = 1;
	ledger->l_size = (int32_t)cnt;

	template_lock(template);
	assert(ledger->l_size <= template->lt_cnt);
	for (i = 0; i < ledger->l_size; i++) {
		struct ledger_entry *le = &ledger->l_entries[i];
		struct entry_template *et = &template->lt_entries[i];

		le->le_flags = et->et_flags;
		/* make entry inactive by removing  active bit */
		if (entry_type == LEDGER_CREATE_INACTIVE_ENTRIES)
			flag_clear(&le->le_flags, LF_ENTRY_ACTIVE);
		/*
		 * If template has a callback, this entry is opted-in,
		 * by default.
		 */
		if (et->et_callback != NULL)
			flag_set(&le->le_flags, LEDGER_ACTION_CALLBACK);
		le->le_credit        = 0;
		le->le_debit         = 0;
		le->le_limit         = LEDGER_LIMIT_INFINITY;
		le->le_warn_level    = LEDGER_LIMIT_INFINITY;		
		le->_le.le_refill.le_refill_period = 0;
		le->_le.le_refill.le_last_refill   = 0;
	}
	template_unlock(template);

	return (ledger);
}