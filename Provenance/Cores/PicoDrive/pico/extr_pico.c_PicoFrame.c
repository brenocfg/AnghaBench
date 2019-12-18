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
struct TYPE_3__ {int /*<<< orphan*/  frame_count; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int PAHW_32X ; 
 int PAHW_MCD ; 
 int PAHW_SMS ; 
 TYPE_2__ Pico ; 
 int PicoAHW ; 
 int /*<<< orphan*/  PicoFrame32x () ; 
 int /*<<< orphan*/  PicoFrameHints () ; 
 int /*<<< orphan*/  PicoFrameMCD () ; 
 int /*<<< orphan*/  PicoFrameMS () ; 
 int /*<<< orphan*/  PicoFrameStart () ; 
 int /*<<< orphan*/  frame ; 
 int /*<<< orphan*/  pprof_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pprof_start (int /*<<< orphan*/ ) ; 

void PicoFrame(void)
{
  pprof_start(frame);

  Pico.m.frame_count++;

  if (PicoAHW & PAHW_SMS) {
    PicoFrameMS();
    goto end;
  }

  if (PicoAHW & PAHW_32X) {
    PicoFrame32x(); // also does MCD+32X
    goto end;
  }

  if (PicoAHW & PAHW_MCD) {
    PicoFrameMCD();
    goto end;
  }

  //if(Pico.video.reg[12]&0x2) Pico.video.status ^= 0x10; // change odd bit in interlace mode

  PicoFrameStart();
  PicoFrameHints();

end:
  pprof_end(frame);
}