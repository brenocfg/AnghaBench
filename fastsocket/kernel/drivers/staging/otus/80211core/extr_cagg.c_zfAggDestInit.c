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
typedef  int u16_t ;
struct TYPE_2__ {void (* init ) (int /*<<< orphan*/ *) ;scalar_t__ ppri; int /*<<< orphan*/  exist; int /*<<< orphan*/  getNext; int /*<<< orphan*/  delete; int /*<<< orphan*/  insert; int /*<<< orphan*/ ** Head; } ;

/* Variables and functions */
 TYPE_1__ DESTQ ; 
 int /*<<< orphan*/  zfAggDestDelete ; 
 int /*<<< orphan*/  zfAggDestExist ; 
 int /*<<< orphan*/  zfAggDestGetNext ; 
 int /*<<< orphan*/  zfAggDestInsert ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void    zfAggDestInit(zdev_t* dev)
{
    u16_t i;
    zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();

    for (i=0; i<4; i++) {
        //wd->destQ.Head[i].next = wd->destQ.Head[i];
        //wd->destQ.dest[i] = wd->destQ.Head[i];
        //DESTQ.size[i] = 0;
        DESTQ.Head[i] = NULL;
    }
    DESTQ.insert  = zfAggDestInsert;
    DESTQ.delete  = zfAggDestDelete;
    DESTQ.init    = zfAggDestInit;
    DESTQ.getNext = zfAggDestGetNext;
    DESTQ.exist   = zfAggDestExist;
    DESTQ.ppri = 0;
    return;
}