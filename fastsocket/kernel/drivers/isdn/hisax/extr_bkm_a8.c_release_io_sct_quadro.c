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
struct TYPE_3__ {int base; int plx_adr; } ;
struct TYPE_4__ {TYPE_1__ ax; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ SCT_1 ; 
 int /*<<< orphan*/  release_region (int,int) ; 

__attribute__((used)) static void
release_io_sct_quadro(struct IsdnCardState *cs)
{
	release_region(cs->hw.ax.base & 0xffffffc0, 128);
	if (cs->subtyp == SCT_1)
		release_region(cs->hw.ax.plx_adr, 64);
}