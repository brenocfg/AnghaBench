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
struct op_sample {int /*<<< orphan*/  event; int /*<<< orphan*/  eip; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  sample_lost_no_mapping; int /*<<< orphan*/  sample_lost_no_mm; } ;

/* Variables and functions */
 unsigned long INVALID_COOKIE ; 
 int /*<<< orphan*/  add_cookie_switch (unsigned long) ; 
 int /*<<< orphan*/  add_sample_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned long last_cookie ; 
 unsigned long lookup_dcookie (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ oprofile_stats ; 

__attribute__((used)) static int
add_sample(struct mm_struct *mm, struct op_sample *s, int in_kernel)
{
	unsigned long cookie;
	off_t offset;

	if (in_kernel) {
		add_sample_entry(s->eip, s->event);
		return 1;
	}

	/* add userspace sample */

	if (!mm) {
		atomic_inc(&oprofile_stats.sample_lost_no_mm);
		return 0;
	}

	cookie = lookup_dcookie(mm, s->eip, &offset);

	if (cookie == INVALID_COOKIE) {
		atomic_inc(&oprofile_stats.sample_lost_no_mapping);
		return 0;
	}

	if (cookie != last_cookie) {
		add_cookie_switch(cookie);
		last_cookie = cookie;
	}

	add_sample_entry(offset, s->event);

	return 1;
}