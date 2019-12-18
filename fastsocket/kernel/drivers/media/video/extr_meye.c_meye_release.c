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
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mchip_dma_free () ; 
 int /*<<< orphan*/  mchip_hic_stop () ; 
 TYPE_1__ meye ; 

__attribute__((used)) static int meye_release(struct file *file)
{
	mchip_hic_stop();
	mchip_dma_free();
	clear_bit(0, &meye.in_use);
	return 0;
}