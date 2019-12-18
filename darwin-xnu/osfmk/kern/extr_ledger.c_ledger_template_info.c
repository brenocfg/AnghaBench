#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ledger_template_info {int /*<<< orphan*/  lti_units; int /*<<< orphan*/  lti_group; int /*<<< orphan*/  lti_name; } ;
struct entry_template {int /*<<< orphan*/  et_units; int /*<<< orphan*/  et_group; int /*<<< orphan*/  et_key; } ;
typedef  TYPE_1__* ledger_t ;
struct TYPE_7__ {TYPE_1__* ledger; } ;
struct TYPE_6__ {struct entry_template* lt_entries; } ;
struct TYPE_5__ {int l_size; TYPE_2__* l_template; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LEDGER_NAME_MAX ; 
 TYPE_4__* current_task () ; 
 struct ledger_template_info* kalloc (int) ; 
 int /*<<< orphan*/  memset (struct ledger_template_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  template_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  template_unlock (TYPE_2__*) ; 

int
ledger_template_info(void **buf, int *len)
{
	struct ledger_template_info *lti;
	struct entry_template *et;
	int i;
	ledger_t l;

	/*
	 * Since all tasks share a ledger template, we'll just use the
	 * caller's as the source.
	 */
	l = current_task()->ledger;
	if ((*len < 0) || (l == NULL))
		return (EINVAL);

	if (*len > l->l_size)
		 *len = l->l_size;
	lti = kalloc((*len) * sizeof (struct ledger_template_info));
	if (lti == NULL)
		return (ENOMEM);
	*buf = lti;

	template_lock(l->l_template);
	et = l->l_template->lt_entries;

	for (i = 0; i < *len; i++) {
		memset(lti, 0, sizeof (*lti));
		strlcpy(lti->lti_name, et->et_key, LEDGER_NAME_MAX);
		strlcpy(lti->lti_group, et->et_group, LEDGER_NAME_MAX);
		strlcpy(lti->lti_units, et->et_units, LEDGER_NAME_MAX);
		et++;
		lti++;
	}
	template_unlock(l->l_template);

	return (0);
}