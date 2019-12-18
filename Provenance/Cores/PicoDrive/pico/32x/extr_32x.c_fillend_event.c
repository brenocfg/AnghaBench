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
struct TYPE_2__ {int /*<<< orphan*/ * vdp_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  P32XV_nFEN ; 
 TYPE_1__ Pico32x ; 
 int /*<<< orphan*/  SH2_STATE_VPOLL ; 
 int /*<<< orphan*/  msh2 ; 
 int /*<<< orphan*/  p32x_sh2_poll_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ssh2 ; 

__attribute__((used)) static void fillend_event(unsigned int now)
{
  Pico32x.vdp_regs[0x0a/2] &= ~P32XV_nFEN;
  p32x_sh2_poll_event(&msh2, SH2_STATE_VPOLL, now);
  p32x_sh2_poll_event(&ssh2, SH2_STATE_VPOLL, now);
}