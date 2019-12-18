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
struct TYPE_2__ {scalar_t__ type; scalar_t__ objectid; scalar_t__ offset; } ;
struct __prelim_ref {scalar_t__ level; scalar_t__ root_id; scalar_t__ parent; TYPE_1__ key_for_search; } ;

/* Variables and functions */

__attribute__((used)) static inline int ref_for_same_block(struct __prelim_ref *ref1,
				     struct __prelim_ref *ref2)
{
	if (ref1->level != ref2->level)
		return 0;
	if (ref1->root_id != ref2->root_id)
		return 0;
	if (ref1->key_for_search.type != ref2->key_for_search.type)
		return 0;
	if (ref1->key_for_search.objectid != ref2->key_for_search.objectid)
		return 0;
	if (ref1->key_for_search.offset != ref2->key_for_search.offset)
		return 0;
	if (ref1->parent != ref2->parent)
		return 0;

	return 1;
}