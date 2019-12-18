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
struct hpsb_highlevel {int /*<<< orphan*/  host_info_lock; int /*<<< orphan*/  host_info_list; int /*<<< orphan*/  name; } ;
struct hl_host_info {size_t size; int /*<<< orphan*/  list; struct hpsb_host* host; struct hl_host_info* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HPSB_ERR (char*,int /*<<< orphan*/ ) ; 
 struct hl_host_info* hl_get_hostinfo (struct hpsb_highlevel*,struct hpsb_host*) ; 
 struct hl_host_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void *hpsb_create_hostinfo(struct hpsb_highlevel *hl, struct hpsb_host *host,
			   size_t data_size)
{
	struct hl_host_info *hi;
	void *data;
	unsigned long flags;

	hi = hl_get_hostinfo(hl, host);
	if (hi) {
		HPSB_ERR("%s called hpsb_create_hostinfo when hostinfo already"
			 " exists", hl->name);
		return NULL;
	}

	hi = kzalloc(sizeof(*hi) + data_size, GFP_ATOMIC);
	if (!hi)
		return NULL;

	if (data_size) {
		data = hi->data = hi + 1;
		hi->size = data_size;
	} else
		data = hi;

	hi->host = host;

	write_lock_irqsave(&hl->host_info_lock, flags);
	list_add_tail(&hi->list, &hl->host_info_list);
	write_unlock_irqrestore(&hl->host_info_lock, flags);

	return data;
}