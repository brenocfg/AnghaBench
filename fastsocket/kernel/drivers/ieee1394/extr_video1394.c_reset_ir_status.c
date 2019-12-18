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
struct dma_iso_ctx {int nb_cmd; int left_size; TYPE_1__** ir_prg; } ;
struct TYPE_2__ {void* status; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void reset_ir_status(struct dma_iso_ctx *d, int n)
{
	int i;
	d->ir_prg[n][0].status = cpu_to_le32(4);
	d->ir_prg[n][1].status = cpu_to_le32(PAGE_SIZE-4);
	for (i = 2; i < d->nb_cmd - 1; i++)
		d->ir_prg[n][i].status = cpu_to_le32(PAGE_SIZE);
	d->ir_prg[n][i].status = cpu_to_le32(d->left_size);
}