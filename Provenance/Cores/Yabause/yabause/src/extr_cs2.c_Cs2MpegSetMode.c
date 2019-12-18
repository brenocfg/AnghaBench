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
typedef  int u8 ;
struct TYPE_5__ {int CR1; int CR2; int CR3; int HIRQ; } ;
struct TYPE_4__ {int vidplaymode; int dectimingmode; int outmode; int slmode; } ;
struct TYPE_6__ {TYPE_2__ reg; int /*<<< orphan*/  status; TYPE_1__ mpegmode; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_MPCM ; 
 TYPE_3__* Cs2Area ; 
 int /*<<< orphan*/  doMPEGReport (int /*<<< orphan*/ ) ; 

void Cs2MpegSetMode(void) {
   u8 vidplaymode=Cs2Area->reg.CR1 & 0xFF;
   u8 dectimingmode=Cs2Area->reg.CR2 >> 8;
   u8 outmode=Cs2Area->reg.CR2 & 0xFF;
   u8 slmode=Cs2Area->reg.CR3 >> 8;

   if (vidplaymode != 0xFF)
      Cs2Area->mpegmode.vidplaymode = vidplaymode;

   if (dectimingmode != 0xFF)
      Cs2Area->mpegmode.dectimingmode = dectimingmode;

   if (outmode != 0xFF)
      Cs2Area->mpegmode.outmode = outmode;

   if (slmode != 0xFF)
      Cs2Area->mpegmode.slmode = slmode;

   doMPEGReport(Cs2Area->status);
   Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_MPCM;
}