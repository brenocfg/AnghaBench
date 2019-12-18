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
struct dccp_ackvec_record {int /*<<< orphan*/  avr_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dccp_ackvec_record_slab ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dccp_ackvec_record*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_ackvec_record_delete(struct dccp_ackvec_record *avr)
{
	if (unlikely(avr == NULL))
		return;
	/* Check if deleting a linked record */
	WARN_ON(!list_empty(&avr->avr_node));
	kmem_cache_free(dccp_ackvec_record_slab, avr);
}