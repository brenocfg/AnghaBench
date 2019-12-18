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
typedef  int u64 ;
struct spu {TYPE_1__* priv1; } ;
struct TYPE_2__ {int /*<<< orphan*/ * int_mask_RW; } ;

/* Variables and functions */
 int in_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void int_mask_or(struct spu *spu, int class, u64 mask)
{
	u64 old_mask;

	old_mask = in_be64(&spu->priv1->int_mask_RW[class]);
	out_be64(&spu->priv1->int_mask_RW[class], old_mask | mask);
}