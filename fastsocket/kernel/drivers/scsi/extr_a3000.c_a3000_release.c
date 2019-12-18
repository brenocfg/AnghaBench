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
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {scalar_t__ CNTR; } ;

/* Variables and functions */
 TYPE_1__* DMA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  IRQ_AMIGA_PORTS ; 
 int /*<<< orphan*/  a3000_intr ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int,int) ; 
 int /*<<< orphan*/  wd33c93_release () ; 

__attribute__((used)) static int a3000_release(struct Scsi_Host *instance)
{
    wd33c93_release();
    DMA(instance)->CNTR = 0;
    release_mem_region(0xDD0000, 256);
    free_irq(IRQ_AMIGA_PORTS, a3000_intr);
    return 1;
}