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
struct TYPE_3__ {int first_segment; int buffer1_size; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct dma_desc {TYPE_2__ des01; } ;

/* Variables and functions */

__attribute__((used)) static void mac100_prepare_tx_desc(struct dma_desc *p, int is_fs, int len,
				   int csum_flag)
{
	p->des01.tx.first_segment = is_fs;
	p->des01.tx.buffer1_size = len;
}