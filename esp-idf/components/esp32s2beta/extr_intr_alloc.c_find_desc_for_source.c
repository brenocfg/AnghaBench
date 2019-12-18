#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int source; int cpu; struct TYPE_5__* next; TYPE_2__* shared_vec_info; } ;
typedef  TYPE_1__ vector_desc_t ;
struct TYPE_6__ {int source; struct TYPE_6__* next; } ;
typedef  TYPE_2__ shared_vector_desc_t ;

/* Variables and functions */
 int VECDESC_FL_SHARED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* vector_desc_head ; 

__attribute__((used)) static vector_desc_t * find_desc_for_source(int source, int cpu)
{
    vector_desc_t *vd=vector_desc_head;
    while(vd!=NULL) {
        if ( !(vd->flags & VECDESC_FL_SHARED) ) {
            if ( vd->source == source && cpu == vd->cpu ) break;
        } else if ( vd->cpu == cpu ) {
            // check only shared vds for the correct cpu, otherwise skip
            bool found = false;
            shared_vector_desc_t *svd = vd->shared_vec_info;
            assert(svd != NULL );
            while(svd) {
                if ( svd->source == source ) {
                    found = true;
                    break;
                }
                svd = svd->next;
            }
            if ( found ) break;
        }
        vd=vd->next;
    }
    return vd;
}