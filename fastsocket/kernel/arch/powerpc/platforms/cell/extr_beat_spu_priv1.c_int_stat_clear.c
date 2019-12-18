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
typedef  int /*<<< orphan*/  u64 ;
struct spu {int /*<<< orphan*/  spe_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  beat_clear_interrupt_status_of_spe (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int_stat_clear(struct spu *spu, int class, u64 stat)
{
	beat_clear_interrupt_status_of_spe(spu->spe_id, class, stat);
}