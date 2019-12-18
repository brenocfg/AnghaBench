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
 int /*<<< orphan*/  DrawBlankedLine (int,int,int,int) ; 
 int DrawScanline ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  PicoLine (int,int,int,int) ; 
 int /*<<< orphan*/  draw ; 
 int /*<<< orphan*/  pprof_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pprof_start (int /*<<< orphan*/ ) ; 
 int rendlines ; 

void PicoDrawSync(int to, int blank_last_line)
{
  int line, offs = 0;
  int sh = (Pico.video.reg[0xC] & 8) >> 3; // shadow/hilight?
  int bgc = Pico.video.reg[7];

  pprof_start(draw);

  if (rendlines != 240)
    offs = 8;

  for (line = DrawScanline; line < to; line++)
  {
    PicoLine(line, offs, sh, bgc);
  }

  // last line
  if (line <= to)
  {
    if (blank_last_line)
         DrawBlankedLine(line, offs, sh, bgc);
    else PicoLine(line, offs, sh, bgc);
    line++;
  }
  DrawScanline = line;

  pprof_end(draw);
}