#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ skb; } ;
struct TYPE_4__ {TYPE_2__* sRxDFCB; } ;
typedef  TYPE_1__* PSDevice ;
typedef  TYPE_2__* PSDeFragControlBlock ;

/* Variables and functions */
 int CB_MAX_RX_FRAG ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 

__attribute__((used)) static void device_free_frag_bufs(PSDevice pDevice) {
    PSDeFragControlBlock pDeF;
    int i;

    for (i = 0; i < CB_MAX_RX_FRAG; i++) {

        pDeF = &(pDevice->sRxDFCB[i]);

        if (pDeF->skb)
            dev_kfree_skb(pDeF->skb);
    }
}