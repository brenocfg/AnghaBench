#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostap_cmd_queue {int del_req; int /*<<< orphan*/  usecnt; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_queue_len; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hostap_cmd_queue*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __hostap_cmd_queue_free(local_info_t *local,
					   struct hostap_cmd_queue *entry,
					   int del_req)
{
	if (del_req) {
		entry->del_req = 1;
		if (!list_empty(&entry->list)) {
			list_del_init(&entry->list);
			local->cmd_queue_len--;
		}
	}

	if (atomic_dec_and_test(&entry->usecnt) && entry->del_req)
		kfree(entry);
}