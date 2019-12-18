#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int intno; int flags; } ;
typedef  TYPE_1__ vector_desc_t ;
struct TYPE_5__ {scalar_t__* cpuflags; int level; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALCHLOG (char*) ; 
 int ESP_INTR_FLAG_EDGE ; 
 int ESP_INTR_FLAG_IRAM ; 
 int ESP_INTR_FLAG_SHARED ; 
 scalar_t__ INTDESC_RESVD ; 
 scalar_t__ INTDESC_SPECIAL ; 
 scalar_t__ INTTP_EDGE ; 
 scalar_t__ INTTP_LEVEL ; 
 int VECDESC_FL_INIRAM ; 
 int VECDESC_FL_NONSHARED ; 
 int VECDESC_FL_RESERVED ; 
 int VECDESC_FL_SHARED ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* int_desc ; 
 scalar_t__ int_has_handler (int,int) ; 

__attribute__((used)) static bool is_vect_desc_usable(vector_desc_t *vd, int flags, int cpu, int force)
{
    //Check if interrupt is not reserved by design
    int x = vd->intno;
    if (int_desc[x].cpuflags[cpu]==INTDESC_RESVD) {
        ALCHLOG("....Unusable: reserved");
        return false;
    }
    if (int_desc[x].cpuflags[cpu]==INTDESC_SPECIAL && force==-1) {
        ALCHLOG("....Unusable: special-purpose int");
        return false;
    }
    //Check if the interrupt level is acceptable
    if (!(flags&(1<<int_desc[x].level))) {
        ALCHLOG("....Unusable: incompatible level");
        return false;
    }
    //check if edge/level type matches what we want
    if (((flags&ESP_INTR_FLAG_EDGE) && (int_desc[x].type==INTTP_LEVEL)) ||
            (((!(flags&ESP_INTR_FLAG_EDGE)) && (int_desc[x].type==INTTP_EDGE)))) {
        ALCHLOG("....Unusable: incompatible trigger type");
        return false;
    }
    //check if interrupt is reserved at runtime
    if (vd->flags&VECDESC_FL_RESERVED)  {
        ALCHLOG("....Unusable: reserved at runtime.");
        return false;
    }
    //Ints can't be both shared and non-shared.
    assert(!((vd->flags&VECDESC_FL_SHARED)&&(vd->flags&VECDESC_FL_NONSHARED)));
    //check if interrupt already is in use by a non-shared interrupt
    if (vd->flags&VECDESC_FL_NONSHARED) {
        ALCHLOG("....Unusable: already in (non-shared) use.");
        return false;
    }
    // check shared interrupt flags
    if (vd->flags&VECDESC_FL_SHARED ) {
        if (flags&ESP_INTR_FLAG_SHARED) {
            bool in_iram_flag=((flags&ESP_INTR_FLAG_IRAM)!=0);
            bool desc_in_iram_flag=((vd->flags&VECDESC_FL_INIRAM)!=0);
            //Bail out if int is shared, but iram property doesn't match what we want.
            if ((vd->flags&VECDESC_FL_SHARED) && (desc_in_iram_flag!=in_iram_flag))  {
                ALCHLOG("....Unusable: shared but iram prop doesn't match");
                return false;
            }
        } else {
            //We need an unshared IRQ; can't use shared ones; bail out if this is shared.
            ALCHLOG("...Unusable: int is shared, we need non-shared.");
            return false;
        }
    } else if (int_has_handler(x, cpu)) {
        //Check if interrupt already is allocated by xt_set_interrupt_handler
        ALCHLOG("....Unusable: already allocated");
        return false;
    }
    return true;
}