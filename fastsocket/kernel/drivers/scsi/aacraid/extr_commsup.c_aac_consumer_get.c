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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * consumer; int /*<<< orphan*/ * producer; } ;
struct aac_queue {scalar_t__ entries; struct aac_entry* base; TYPE_1__ headers; } ;
struct aac_entry {int dummy; } ;
struct aac_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

int aac_consumer_get(struct aac_dev * dev, struct aac_queue * q, struct aac_entry **entry)
{
	u32 index;
	int status;
	if (le32_to_cpu(*q->headers.producer) == le32_to_cpu(*q->headers.consumer)) {
		status = 0;
	} else {
		/*
		 *	The consumer index must be wrapped if we have reached
		 *	the end of the queue, else we just use the entry
		 *	pointed to by the header index
		 */
		if (le32_to_cpu(*q->headers.consumer) >= q->entries)
			index = 0;
		else
			index = le32_to_cpu(*q->headers.consumer);
		*entry = q->base + index;
		status = 1;
	}
	return(status);
}