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
typedef  int /*<<< orphan*/  u64 ;
struct thash_data {scalar_t__ next; int /*<<< orphan*/  etag; scalar_t__ itir; scalar_t__ page_flags; } ;
struct TYPE_2__ {unsigned long val; int vf; int ve; int /*<<< orphan*/  size; } ;
struct thash_cb {int num; struct thash_data* hash; TYPE_1__ pta; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_TI_TAG ; 

void thash_init(struct thash_cb *hcb, u64 sz)
{
	int i;
	struct thash_data *head;

	hcb->pta.val = (unsigned long)hcb->hash;
	hcb->pta.vf = 1;
	hcb->pta.ve = 1;
	hcb->pta.size = sz;
	head = hcb->hash;
	for (i = 0; i < hcb->num; i++) {
		head->page_flags = 0;
		head->itir = 0;
		head->etag = INVALID_TI_TAG;
		head->next = 0;
		head++;
	}
}