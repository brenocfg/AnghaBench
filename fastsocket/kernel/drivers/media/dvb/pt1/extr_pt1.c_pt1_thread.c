#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt1_buffer_page {int dummy; } ;
struct pt1 {TYPE_2__* tables; } ;
struct TYPE_4__ {TYPE_1__* bufs; } ;
struct TYPE_3__ {struct pt1_buffer_page* page; } ;

/* Variables and functions */
 int HZ ; 
 int PT1_NR_BUFS ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  pt1_filter (struct pt1*,struct pt1_buffer_page*) ; 
 int /*<<< orphan*/  pt1_increment_table_count (struct pt1*) ; 
 int pt1_nr_tables ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static int pt1_thread(void *data)
{
	struct pt1 *pt1;
	int table_index;
	int buf_index;
	struct pt1_buffer_page *page;

	pt1 = data;
	set_freezable();

	table_index = 0;
	buf_index = 0;

	while (!kthread_should_stop()) {
		try_to_freeze();

		page = pt1->tables[table_index].bufs[buf_index].page;
		if (!pt1_filter(pt1, page)) {
			schedule_timeout_interruptible((HZ + 999) / 1000);
			continue;
		}

		if (++buf_index >= PT1_NR_BUFS) {
			pt1_increment_table_count(pt1);
			buf_index = 0;
			if (++table_index >= pt1_nr_tables)
				table_index = 0;
		}
	}

	return 0;
}