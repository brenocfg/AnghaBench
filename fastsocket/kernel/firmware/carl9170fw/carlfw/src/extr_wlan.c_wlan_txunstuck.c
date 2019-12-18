#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* tx_queue; } ;
struct TYPE_6__ {TYPE_2__ wlan; } ;
struct TYPE_4__ {scalar_t__ head; } ;

/* Variables and functions */
 TYPE_3__ fw ; 
 int /*<<< orphan*/  set_wlan_txq_dma_addr (unsigned int,int) ; 

__attribute__((used)) static void wlan_txunstuck(unsigned int queue)
{
	set_wlan_txq_dma_addr(queue, ((uint32_t) fw.wlan.tx_queue[queue].head) | 1);
}