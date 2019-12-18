#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  nTxQueue; int /*<<< orphan*/  io_size; int /*<<< orphan*/  chip_id; } ;
struct TYPE_7__ {int multicast_limit; int /*<<< orphan*/  lock; int /*<<< orphan*/  nTxQueues; int /*<<< orphan*/  io_size; int /*<<< orphan*/  chip_id; struct pci_dev* pcid; struct TYPE_7__* prev; struct TYPE_7__* next; } ;
typedef  TYPE_1__* PSDevice ;
typedef  TYPE_2__* PCHIP_INFO ;
typedef  int /*<<< orphan*/  DEVICE_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pDevice_Infos ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL device_init_info(struct pci_dev* pcid, PSDevice* ppDevice,
    PCHIP_INFO pChip_info) {

    PSDevice p;

    memset(*ppDevice,0,sizeof(DEVICE_INFO));

    if (pDevice_Infos == NULL) {
        pDevice_Infos =*ppDevice;
    }
    else {
        for (p=pDevice_Infos;p->next!=NULL;p=p->next)
            do {} while (0);
        p->next = *ppDevice;
        (*ppDevice)->prev = p;
    }

    (*ppDevice)->pcid = pcid;
    (*ppDevice)->chip_id = pChip_info->chip_id;
    (*ppDevice)->io_size = pChip_info->io_size;
    (*ppDevice)->nTxQueues = pChip_info->nTxQueue;
    (*ppDevice)->multicast_limit =32;

    spin_lock_init(&((*ppDevice)->lock));

    return TRUE;
}