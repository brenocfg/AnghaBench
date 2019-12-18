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
typedef  scalar_t__ u32 ;
struct tcf_proto {scalar_t__ root; } ;
struct fw_head {struct fw_filter** ht; } ;
struct fw_filter {scalar_t__ id; struct fw_filter* next; } ;

/* Variables and functions */
 size_t fw_hash (scalar_t__) ; 

__attribute__((used)) static unsigned long fw_get(struct tcf_proto *tp, u32 handle)
{
	struct fw_head *head = (struct fw_head*)tp->root;
	struct fw_filter *f;

	if (head == NULL)
		return 0;

	for (f=head->ht[fw_hash(handle)]; f; f=f->next) {
		if (f->id == handle)
			return (unsigned long)f;
	}
	return 0;
}