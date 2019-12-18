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
 int /*<<< orphan*/  BackFill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawDisplayM4 (int) ; 
 char* DrawLineDest ; 
 int DrawLineDestIncrement ; 
 int /*<<< orphan*/  FinalizeLineM4 (int) ; 
 TYPE_2__ Pico ; 
 scalar_t__ PicoScanBegin (scalar_t__) ; 
 scalar_t__ PicoScanEnd (scalar_t__) ; 
 scalar_t__ screen_offset ; 
 scalar_t__ skip_next_line ; 

void PicoLineMode4(int line)
{
  if (skip_next_line > 0) {
    skip_next_line--;
    return;
  }

  if (PicoScanBegin != NULL)
    skip_next_line = PicoScanBegin(line + screen_offset);

  // Draw screen:
  BackFill(Pico.video.reg[7] & 0x0f, 0);
  if (Pico.video.reg[1] & 0x40)
    DrawDisplayM4(line);

  if (FinalizeLineM4 != NULL)
    FinalizeLineM4(line);

  if (PicoScanEnd != NULL)
    skip_next_line = PicoScanEnd(line + screen_offset);

  DrawLineDest = (char *)DrawLineDest + DrawLineDestIncrement;
}