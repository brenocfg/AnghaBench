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
typedef  int u32 ;
struct TYPE_2__ {int* vdp_regs; int vdp_fbcr_fake; } ;

/* Variables and functions */
 int P32XV_HBLK ; 
 int P32XV_nFEN ; 
 TYPE_1__ Pico32x ; 

__attribute__((used)) static u32 p32x_vdp_read16(u32 a)
{
  u32 d;
  a &= 0x0e;

  d = Pico32x.vdp_regs[a / 2];
  if (a == 0x0a) {
    // tested: FEN seems to be randomly pulsing on hcnt 0x80-0xf0,
    // most often at 0xb1-0xb5, even during vblank,
    // what's the deal with that?
    // we'll just fake it along with hblank for now
    Pico32x.vdp_fbcr_fake++;
    if (Pico32x.vdp_fbcr_fake & 4)
      d |= P32XV_HBLK;
    if ((Pico32x.vdp_fbcr_fake & 7) == 0)
      d |= P32XV_nFEN;
  }
  return d;
}