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
struct TYPE_3__ {int pending_ints; scalar_t__ pending; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SR ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned char) ; 

__attribute__((used)) static unsigned char vdp_ctl_read(void)
{
  unsigned char d = Pico.video.pending_ints << 7;
  Pico.video.pending = 0;
  Pico.video.pending_ints = 0;

  elprintf(EL_SR, "VDP sr: %02x", d);
  return d;
}