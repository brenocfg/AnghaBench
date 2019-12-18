#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  PtdCntrl; } ;

/* Variables and functions */
 TYPE_2__* bcom_eng ; 
 int in_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void bcom_disable_prefetch(void)
{
	u16 regval;

	regval = in_be16(&bcom_eng->regs->PtdCntrl);
	out_be16(&bcom_eng->regs->PtdCntrl, regval | 1);
}