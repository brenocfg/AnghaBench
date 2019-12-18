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
struct hpsb_host {int dummy; } ;
struct host_info {int /*<<< orphan*/  list; int /*<<< orphan*/  file_info_list; struct hpsb_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_count ; 
 int /*<<< orphan*/  host_info_list ; 
 int /*<<< orphan*/  host_info_lock ; 
 int /*<<< orphan*/  internal_generation ; 
 struct host_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void add_host(struct hpsb_host *host)
{
	struct host_info *hi;
	unsigned long flags;

	hi = kmalloc(sizeof(*hi), GFP_KERNEL);

	if (hi) {
		INIT_LIST_HEAD(&hi->list);
		hi->host = host;
		INIT_LIST_HEAD(&hi->file_info_list);

		spin_lock_irqsave(&host_info_lock, flags);
		list_add_tail(&hi->list, &host_info_list);
		host_count++;
		spin_unlock_irqrestore(&host_info_lock, flags);
	}

	atomic_inc(&internal_generation);
}