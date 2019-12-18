#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct entry_template {int /*<<< orphan*/ * et_callback; int /*<<< orphan*/  et_flags; int /*<<< orphan*/  et_units; int /*<<< orphan*/  et_group; int /*<<< orphan*/  et_key; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  TYPE_1__* ledger_template_t ;
struct TYPE_7__ {size_t lt_cnt; size_t lt_table_size; struct entry_template* lt_entries; int /*<<< orphan*/ * lt_zone; } ;

/* Variables and functions */
 scalar_t__ LEDGER_NAME_MAX ; 
 int /*<<< orphan*/  LF_ENTRY_ACTIVE ; 
 int /*<<< orphan*/  TEMPLATE_IDLE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TEMPLATE_INUSE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct entry_template* kalloc (int) ; 
 int /*<<< orphan*/  kfree (struct entry_template*,int) ; 
 int /*<<< orphan*/  memcpy (struct entry_template*,struct entry_template*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_mul_overflow (int,int,int*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  template_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  template_unlock (TYPE_1__*) ; 

int
ledger_entry_add(ledger_template_t template, const char *key,
    const char *group, const char *units)
{
	int idx;
	struct entry_template *et;

	if ((key == NULL) || (strlen(key) >= LEDGER_NAME_MAX) || (template->lt_zone != NULL))
		return (-1);

	template_lock(template);

	/* If the table is full, attempt to double its size */
	if (template->lt_cnt == template->lt_table_size) {
		struct entry_template *new_entries, *old_entries;
		int old_cnt, old_sz, new_sz = 0;
		spl_t s;

		old_cnt = template->lt_table_size;
		old_sz = old_cnt * (int)(sizeof(struct entry_template));
		/* double old_sz allocation, but check for overflow */
		if (os_mul_overflow(old_sz, 2, &new_sz)) {
			template_unlock(template);
			return -1;
		}
		new_entries = kalloc(new_sz);
		if (new_entries == NULL) {
			template_unlock(template);
			return -1;
		}
		memcpy(new_entries, template->lt_entries, old_sz);
		memset(((char *)new_entries) + old_sz, 0, old_sz);
		/* assume: if the sz didn't overflow, neither will the count */
		template->lt_table_size = old_cnt * 2;

		old_entries = template->lt_entries;

		TEMPLATE_INUSE(s, template);
		template->lt_entries = new_entries;
		TEMPLATE_IDLE(s, template);

		kfree(old_entries, old_sz);
	}

	et = &template->lt_entries[template->lt_cnt];
	strlcpy(et->et_key, key, LEDGER_NAME_MAX);
	strlcpy(et->et_group, group, LEDGER_NAME_MAX);
	strlcpy(et->et_units, units, LEDGER_NAME_MAX);
	et->et_flags = LF_ENTRY_ACTIVE;
	et->et_callback = NULL;

	idx = template->lt_cnt++;
	template_unlock(template);

	return (idx);
}