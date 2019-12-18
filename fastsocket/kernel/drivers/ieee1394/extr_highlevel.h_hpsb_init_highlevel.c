#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hpsb_highlevel {int /*<<< orphan*/  host_info_list; int /*<<< orphan*/  host_info_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hpsb_init_highlevel(struct hpsb_highlevel *hl)
{
	rwlock_init(&hl->host_info_lock);
	INIT_LIST_HEAD(&hl->host_info_list);
}