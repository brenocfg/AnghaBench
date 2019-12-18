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
struct TYPE_3__ {int first_segment; int buffer1_size; int buffer2_size; int /*<<< orphan*/  checksum_insertion; } ;
struct TYPE_4__ {TYPE_1__ etx; } ;
struct dma_desc {TYPE_2__ des01; } ;

/* Variables and functions */
 int BUF_SIZE_4KiB ; 
 int /*<<< orphan*/  cic_full ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void gmac_prepare_tx_desc(struct dma_desc *p, int is_fs, int len,
				 int csum_flag)
{
	p->des01.etx.first_segment = is_fs;
	if (unlikely(len > BUF_SIZE_4KiB)) {
		p->des01.etx.buffer1_size = BUF_SIZE_4KiB;
		p->des01.etx.buffer2_size = len - BUF_SIZE_4KiB;
	} else {
		p->des01.etx.buffer1_size = len;
	}
	if (likely(csum_flag))
		p->des01.etx.checksum_insertion = cic_full;
}