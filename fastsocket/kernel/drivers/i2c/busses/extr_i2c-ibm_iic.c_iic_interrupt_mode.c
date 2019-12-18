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
struct ibm_iic_private {TYPE_1__* vaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  intmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTRMSK_EIMTC ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iic_interrupt_mode(struct ibm_iic_private* dev, int enable)
{
	out_8(&dev->vaddr->intmsk, enable ? INTRMSK_EIMTC : 0);
}