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
struct atyfb_par {scalar_t__ blitter_may_be_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUI_STAT ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  wait_for_fifo (int,struct atyfb_par*) ; 

__attribute__((used)) static inline void wait_for_idle(struct atyfb_par *par)
{
	wait_for_fifo(16, par);
	while ((aty_ld_le32(GUI_STAT, par) & 1) != 0);
	par->blitter_may_be_busy = 0;
}