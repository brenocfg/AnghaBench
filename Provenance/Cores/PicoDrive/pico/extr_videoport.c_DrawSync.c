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
struct TYPE_3__ {int scanline; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int DrawScanline ; 
 int POPT_ALT_RENDERER ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  PicoDrawSync (int,int) ; 
 int PicoOpt ; 
 int /*<<< orphan*/  PicoSkipFrame ; 

__attribute__((used)) static void DrawSync(int blank_on)
{
  if (Pico.m.scanline < 224 && !(PicoOpt & POPT_ALT_RENDERER) &&
      !PicoSkipFrame && DrawScanline <= Pico.m.scanline) {
    //elprintf(EL_ANOMALY, "sync");
    PicoDrawSync(Pico.m.scanline, blank_on);
  }
}