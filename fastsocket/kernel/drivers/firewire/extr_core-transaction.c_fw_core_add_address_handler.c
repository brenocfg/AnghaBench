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
struct fw_address_region {int start; int end; } ;
struct fw_address_handler {int length; int offset; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  address_handler_list ; 
 int /*<<< orphan*/  address_handler_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fw_address_handler* lookup_overlapping_address_handler (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int fw_core_add_address_handler(struct fw_address_handler *handler,
				const struct fw_address_region *region)
{
	struct fw_address_handler *other;
	unsigned long flags;
	int ret = -EBUSY;

	if (region->start & 0xffff000000000003ULL ||
	    region->end   & 0xffff000000000003ULL ||
	    region->start >= region->end ||
	    handler->length & 3 ||
	    handler->length == 0)
		return -EINVAL;

	spin_lock_irqsave(&address_handler_lock, flags);

	handler->offset = region->start;
	while (handler->offset + handler->length <= region->end) {
		other =
		    lookup_overlapping_address_handler(&address_handler_list,
						       handler->offset,
						       handler->length);
		if (other != NULL) {
			handler->offset += other->length;
		} else {
			list_add_tail(&handler->link, &address_handler_list);
			ret = 0;
			break;
		}
	}

	spin_unlock_irqrestore(&address_handler_lock, flags);

	return ret;
}