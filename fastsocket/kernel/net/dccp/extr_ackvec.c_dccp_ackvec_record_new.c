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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp_ackvec_record_slab ; 
 struct dccp_ackvec_record* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dccp_ackvec_record *dccp_ackvec_record_new(void)
{
	struct dccp_ackvec_record *avr =
			kmem_cache_alloc(dccp_ackvec_record_slab, GFP_ATOMIC);

	if (avr != NULL)
		INIT_LIST_HEAD(&avr->avr_node);

	return avr;
}