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
struct xt_table_info {unsigned int number; int /*<<< orphan*/  initial_entries; } ;
struct xt_table {int /*<<< orphan*/  af; int /*<<< orphan*/  name; struct xt_table_info* private; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  audit_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_NETFILTER_CFG ; 
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ audit_enabled ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  duprintf (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

struct xt_table_info *
xt_replace_table(struct xt_table *table,
	      unsigned int num_counters,
	      struct xt_table_info *newinfo,
	      int *error)
{
	struct xt_table_info *private;

	/* Do the substitution. */
	local_bh_disable();
	private = table->private;

	/* Check inside lock: is the old number correct? */
	if (num_counters != private->number) {
		duprintf("num_counters != table->private->number (%u/%u)\n",
			 num_counters, private->number);
		local_bh_enable();
		*error = -EAGAIN;
		return NULL;
	}

	table->private = newinfo;
	newinfo->initial_entries = private->initial_entries;

	/*
	 * Even though table entries have now been swapped, other CPU's
	 * may still be using the old entries. This is okay, because
	 * resynchronization happens because of the locking done
	 * during the get_counters() routine.
	 */
	local_bh_enable();

#ifdef CONFIG_AUDIT
	if (audit_enabled) {
		struct audit_buffer *ab;

		ab = audit_log_start(current->audit_context, GFP_KERNEL,
				     AUDIT_NETFILTER_CFG);
		if (ab) {
			audit_log_format(ab, "table=%s family=%u entries=%u",
					 table->name, table->af,
					 private->number);
			audit_log_end(ab);
		}
	}
#endif

	return private;
}