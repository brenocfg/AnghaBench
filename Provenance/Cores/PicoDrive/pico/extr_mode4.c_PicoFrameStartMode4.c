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
struct TYPE_3__ {int* reg; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
 char* DrawLineDest ; 
 scalar_t__ DrawLineDestBase ; 
 int DrawLineDestIncrement ; 
 scalar_t__ PDRAW_32_COLS ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  emu_video_mode_change (int,int,int) ; 
 int rendlines ; 
 scalar_t__ rendstatus ; 
 scalar_t__ rendstatus_old ; 
 int screen_offset ; 
 scalar_t__ skip_next_line ; 

void PicoFrameStartMode4(void)
{
  int lines = 192;
  skip_next_line = 0;
  screen_offset = 24;
  rendstatus = PDRAW_32_COLS;

  if ((Pico.video.reg[0] & 6) == 6 && (Pico.video.reg[1] & 0x18)) {
    if (Pico.video.reg[1] & 0x08) {
      screen_offset = 0;
      lines = 240;
    }
    else {
      screen_offset = 8;
      lines = 224;
    }
  }

  if (rendstatus != rendstatus_old || lines != rendlines) {
    emu_video_mode_change(screen_offset, lines, 1);
    rendstatus_old = rendstatus;
    rendlines = lines;
  }

  DrawLineDest = (char *)DrawLineDestBase + screen_offset * DrawLineDestIncrement;
}