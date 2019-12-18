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
struct spu {TYPE_1__* priv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  tlb_invalidate_entry_W; } ;

/* Variables and functions */
 int /*<<< orphan*/  out_be64 (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tlb_invalidate(struct spu *spu)
{
	out_be64(&spu->priv1->tlb_invalidate_entry_W, 0ul);
}