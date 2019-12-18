#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int intno; int cpu; } ;
typedef  TYPE_1__ vector_desc_t ;

/* Variables and functions */
 int MALLOC_CAP_8BIT ; 
 int MALLOC_CAP_INTERNAL ; 
 TYPE_1__* find_desc_for_int (int,int) ; 
 TYPE_1__* heap_caps_malloc (int,int) ; 
 int /*<<< orphan*/  insert_vector_desc (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static vector_desc_t *get_desc_for_int(int intno, int cpu)
{
    vector_desc_t *vd=find_desc_for_int(intno, cpu);
    if (vd==NULL) {
        vector_desc_t *newvd=heap_caps_malloc(sizeof(vector_desc_t), MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT);
        if (newvd==NULL) return NULL;
        memset(newvd, 0, sizeof(vector_desc_t));
        newvd->intno=intno;
        newvd->cpu=cpu;
        insert_vector_desc(newvd);
        return newvd;
    } else {
        return vd;
    }
}