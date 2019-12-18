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
struct TYPE_3__ {int /*<<< orphan*/  phymem; int /*<<< orphan*/  membase; scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ teles0; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  TELES_IOMEM_SIZE ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void
release_io_teles0(struct IsdnCardState *cs)
{
	if (cs->hw.teles0.cfg_reg)
		release_region(cs->hw.teles0.cfg_reg, 8);
	iounmap(cs->hw.teles0.membase);
	release_mem_region(cs->hw.teles0.phymem, TELES_IOMEM_SIZE);
}