#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* reg; } ;
struct TYPE_4__ {int dirtyPal; } ;
struct TYPE_6__ {TYPE_2__ video; scalar_t__ cram; TYPE_1__ m; } ;

/* Variables and functions */
 unsigned char* DrawLineDest ; 
 scalar_t__ HighCol ; 
 unsigned char* HighPal ; 
 int PDRAW_SONIC_MODE ; 
 int POPT_DIS_32C_BORDER ; 
 TYPE_3__ Pico ; 
 int PicoOpt ; 
 int /*<<< orphan*/  blockcpy (unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/  blockcpy_or (unsigned char*,scalar_t__,int,int) ; 
 int rendstatus ; 

__attribute__((used)) static void FinalizeLine8bit(int sh, int line)
{
  unsigned char *pd = DrawLineDest;
  int len, rs = rendstatus;
  static int dirty_count;

  if (!sh && Pico.m.dirtyPal == 1)
  {
    // a hack for mid-frame palette changes
    if (!(rs & PDRAW_SONIC_MODE))
         dirty_count = 1;
    else dirty_count++;
    rs |= PDRAW_SONIC_MODE;
    rendstatus = rs;
    if (dirty_count == 3) {
      blockcpy(HighPal, Pico.cram, 0x40*2);
    } else if (dirty_count == 11) {
      blockcpy(HighPal+0x40, Pico.cram, 0x40*2);
    }
  }

  if (Pico.video.reg[12]&1) {
    len = 320;
  } else {
    if (!(PicoOpt & POPT_DIS_32C_BORDER))
      pd += 32;
    len = 256;
  }

  if (!sh && (rs & PDRAW_SONIC_MODE)) {
    if (dirty_count >= 11) {
      blockcpy_or(pd, HighCol+8, len, 0x80);
    } else {
      blockcpy_or(pd, HighCol+8, len, 0x40);
    }
  } else {
    blockcpy(pd, HighCol+8, len);
  }
}