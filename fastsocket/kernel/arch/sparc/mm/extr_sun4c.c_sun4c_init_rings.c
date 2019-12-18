#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {struct TYPE_15__* prev; struct TYPE_15__* next; } ;
struct TYPE_20__ {scalar_t__ num_entries; TYPE_4__ ringhd; } ;
struct TYPE_16__ {struct TYPE_16__* prev; struct TYPE_16__* next; } ;
struct TYPE_19__ {scalar_t__ num_entries; TYPE_5__ ringhd; } ;
struct TYPE_13__ {struct TYPE_13__* prev; struct TYPE_13__* next; } ;
struct TYPE_18__ {scalar_t__ num_entries; TYPE_2__ ringhd; } ;
struct TYPE_14__ {struct TYPE_14__* lru_prev; struct TYPE_14__* lru_next; } ;
struct TYPE_17__ {scalar_t__ num_entries; TYPE_3__ ringhd; } ;
struct TYPE_12__ {struct TYPE_12__* prev; struct TYPE_12__* next; } ;
struct TYPE_11__ {scalar_t__ num_entries; TYPE_1__ ringhd; } ;

/* Variables and functions */
 int SUN4C_MAX_CONTEXTS ; 
 TYPE_10__* sun4c_context_ring ; 
 TYPE_9__ sun4c_kernel_ring ; 
 TYPE_8__ sun4c_kfree_ring ; 
 TYPE_7__ sun4c_ufree_ring ; 
 TYPE_6__ sun4c_ulru_ring ; 

__attribute__((used)) static inline void sun4c_init_rings(void)
{
	int i;

	for (i = 0; i < SUN4C_MAX_CONTEXTS; i++) {
		sun4c_context_ring[i].ringhd.next =
			sun4c_context_ring[i].ringhd.prev =
			&sun4c_context_ring[i].ringhd;
		sun4c_context_ring[i].num_entries = 0;
	}
	sun4c_ufree_ring.ringhd.next = sun4c_ufree_ring.ringhd.prev =
		&sun4c_ufree_ring.ringhd;
	sun4c_ufree_ring.num_entries = 0;
	sun4c_ulru_ring.ringhd.lru_next = sun4c_ulru_ring.ringhd.lru_prev =
		&sun4c_ulru_ring.ringhd;
	sun4c_ulru_ring.num_entries = 0;
	sun4c_kernel_ring.ringhd.next = sun4c_kernel_ring.ringhd.prev =
		&sun4c_kernel_ring.ringhd;
	sun4c_kernel_ring.num_entries = 0;
	sun4c_kfree_ring.ringhd.next = sun4c_kfree_ring.ringhd.prev =
		&sun4c_kfree_ring.ringhd;
	sun4c_kfree_ring.num_entries = 0;
}