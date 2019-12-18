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
struct TYPE_4__ {int cpu; int intno; struct TYPE_4__* next; } ;
typedef  TYPE_1__ vector_desc_t ;

/* Variables and functions */
 TYPE_1__* vector_desc_head ; 

__attribute__((used)) static vector_desc_t *find_desc_for_int(int intno, int cpu)
{
    vector_desc_t *vd=vector_desc_head;
    while(vd!=NULL) {
        if (vd->cpu==cpu && vd->intno==intno) break;
        vd=vd->next;
    }
    return vd;
}