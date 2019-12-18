#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cpu; scalar_t__ intno; struct TYPE_4__* next; } ;
typedef  TYPE_1__ vector_desc_t ;

/* Variables and functions */
 TYPE_1__* vector_desc_head ; 

__attribute__((used)) static void insert_vector_desc(vector_desc_t *to_insert)
{
    vector_desc_t *vd=vector_desc_head;
    vector_desc_t *prev=NULL;
    while(vd!=NULL) {
        if (vd->cpu > to_insert->cpu) break;
        if (vd->cpu == to_insert->cpu && vd->intno >= to_insert->intno) break;
        prev=vd;
        vd=vd->next;
    }
    if ((vector_desc_head==NULL) || (prev==NULL)) {
        //First item
        to_insert->next = vd;
        vector_desc_head=to_insert;
    } else {
        prev->next=to_insert;
        to_insert->next=vd;
    }
}