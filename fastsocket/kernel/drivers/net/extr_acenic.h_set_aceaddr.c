#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int addrlo; int addrhi; } ;
typedef  TYPE_1__ aceaddr ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void set_aceaddr(aceaddr *aa, dma_addr_t addr)
{
	u64 baddr = (u64) addr;
	aa->addrlo = baddr & 0xffffffff;
	aa->addrhi = baddr >> 32;
	wmb();
}