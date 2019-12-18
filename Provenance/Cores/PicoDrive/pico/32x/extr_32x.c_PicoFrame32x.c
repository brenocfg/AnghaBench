#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ scanline; } ;
struct TYPE_10__ {TYPE_1__ m; } ;
struct TYPE_9__ {int* vdp_regs; int* sh2_regs; int emu_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32X ; 
 int P32XV_Mx ; 
 int P32XV_PEN ; 
 int P32XV_VBLK ; 
 int PAHW_MCD ; 
 TYPE_6__ Pico ; 
 TYPE_5__ Pico32x ; 
 int PicoAHW ; 
 int /*<<< orphan*/  PicoFrameHints () ; 
 int /*<<< orphan*/  PicoFrameStart () ; 
 int /*<<< orphan*/  SH2_STATE_VPOLL ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ msh2 ; 
 int /*<<< orphan*/  p32x_schedule_hint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p32x_sh2_poll_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcd_prepare_frame () ; 
 int /*<<< orphan*/  sh2_drc_frame () ; 
 TYPE_2__ ssh2 ; 

void PicoFrame32x(void)
{
  Pico.m.scanline = 0;

  Pico32x.vdp_regs[0x0a/2] &= ~P32XV_VBLK; // get out of vblank
  if ((Pico32x.vdp_regs[0] & P32XV_Mx) != 0) // no forced blanking
    Pico32x.vdp_regs[0x0a/2] &= ~P32XV_PEN; // no palette access

  if (!(Pico32x.sh2_regs[0] & 0x80))
    p32x_schedule_hint(NULL, SekCyclesDone());
  p32x_sh2_poll_event(&msh2, SH2_STATE_VPOLL, 0);
  p32x_sh2_poll_event(&ssh2, SH2_STATE_VPOLL, 0);

  if (PicoAHW & PAHW_MCD)
    pcd_prepare_frame();

  PicoFrameStart();
  PicoFrameHints();
  sh2_drc_frame();

  elprintf(EL_32X, "poll: %02x %02x %02x",
    Pico32x.emu_flags & 3, msh2.state, ssh2.state);
}