#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/ * BiosRom ; 
 int /*<<< orphan*/ * BupRam ; 
 int /*<<< orphan*/  CartDeInit () ; 
 int /*<<< orphan*/  CheatDeInit () ; 
 int /*<<< orphan*/  Cs2DeInit () ; 
 int /*<<< orphan*/ * HighWram ; 
 int /*<<< orphan*/ * LowWram ; 
 int /*<<< orphan*/  PerDeInit () ; 
 int /*<<< orphan*/  SH2DeInit () ; 
 int /*<<< orphan*/  ScspDeInit () ; 
 int /*<<< orphan*/  ScuDeInit () ; 
 int /*<<< orphan*/  SmpcDeInit () ; 
 scalar_t__ T123Save (int /*<<< orphan*/ *,int,int,scalar_t__) ; 
 int /*<<< orphan*/  T1MemoryDeInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T2MemoryDeInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Vdp1DeInit () ; 
 int /*<<< orphan*/  Vdp2DeInit () ; 
 int /*<<< orphan*/  VideoDeInit () ; 
 int /*<<< orphan*/  YAB_ERR_FILEWRITE ; 
 int /*<<< orphan*/  YabSetError (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ bupfilename ; 

void YabauseDeInit(void) {
   SH2DeInit();

   if (BiosRom)
      T2MemoryDeInit(BiosRom);
   BiosRom = NULL;

   if (HighWram)
      T2MemoryDeInit(HighWram);
   HighWram = NULL;

   if (LowWram)
      T2MemoryDeInit(LowWram);
   LowWram = NULL;

   if (BupRam)
   {
      if (T123Save(BupRam, 0x10000, 1, bupfilename) != 0)
         YabSetError(YAB_ERR_FILEWRITE, (void *)bupfilename);

      T1MemoryDeInit(BupRam);
   }
   BupRam = NULL;

   CartDeInit();
   Cs2DeInit();
   ScuDeInit();
   ScspDeInit();
   Vdp1DeInit();
   Vdp2DeInit();
   SmpcDeInit();
   PerDeInit();
   VideoDeInit();
   CheatDeInit();
}