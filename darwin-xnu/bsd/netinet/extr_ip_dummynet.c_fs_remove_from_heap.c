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
struct dn_heap {int elements; TYPE_1__* p; } ;
struct dn_flow_set {int dummy; } ;
struct dn_flow_queue {struct dn_flow_set* fs; } ;
struct TYPE_2__ {scalar_t__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  heapify (struct dn_heap*) ; 

__attribute__((used)) static void
fs_remove_from_heap(struct dn_heap *h, struct dn_flow_set *fs)
{
    int i = 0, found = 0 ;
    for (; i < h->elements ;)
	if ( ((struct dn_flow_queue *)h->p[i].object)->fs == fs) {
	    h->elements-- ;
	    h->p[i] = h->p[h->elements] ;
	    found++ ;
	} else
	    i++ ;
    if (found)
	heapify(h);
}