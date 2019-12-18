#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rx {int /*<<< orphan*/  dma_addr; scalar_t__ skb; } ;
struct nic {scalar_t__ ru_running; struct rx* rxs; } ;

/* Variables and functions */
 scalar_t__ RU_RUNNING ; 
 scalar_t__ RU_SUSPENDED ; 
 int /*<<< orphan*/  e100_exec_cmd (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ruc_start ; 

__attribute__((used)) static inline void e100_start_receiver(struct nic *nic, struct rx *rx)
{
	if (!nic->rxs) return;
	if (RU_SUSPENDED != nic->ru_running) return;

	/* handle init time starts */
	if (!rx) rx = nic->rxs;

	/* (Re)start RU if suspended or idle and RFA is non-NULL */
	if (rx->skb) {
		e100_exec_cmd(nic, ruc_start, rx->dma_addr);
		nic->ru_running = RU_RUNNING;
	}
}