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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u16_t ;
struct dest {struct dest* next; void* vtxq; void* tid_tx; scalar_t__ Qtype; } ;
struct TYPE_2__ {struct dest** dest; struct dest** Head; } ;
typedef  void* TID_TX ;

/* Variables and functions */
 TYPE_1__ DESTQ ; 
 struct dest* zfwMemAllocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void    zfAggDestInsert(zdev_t* dev, u16_t Qtype, u16_t ac, TID_TX tid_tx, void* vtxq)
{
    struct dest* new_dest;
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    new_dest = zfwMemAllocate(dev, sizeof(struct dest));
    if(!new_dest)
    {
        return;
    }
    new_dest->Qtype = Qtype;
    new_dest->tid_tx = tid_tx;
    if (0 == Qtype)
        new_dest->tid_tx = tid_tx;
    else
        new_dest->vtxq = vtxq;
    if (!DESTQ.Head[ac]) {

        zmw_enter_critical_section(dev);
        new_dest->next = new_dest;
        DESTQ.Head[ac] = DESTQ.dest[ac] = new_dest;
        zmw_leave_critical_section(dev);
    }
    else {

        zmw_enter_critical_section(dev);
        new_dest->next = DESTQ.dest[ac]->next;
        DESTQ.dest[ac]->next = new_dest;
        zmw_leave_critical_section(dev);
    }


    //DESTQ.size[ac]++;
    return;
}