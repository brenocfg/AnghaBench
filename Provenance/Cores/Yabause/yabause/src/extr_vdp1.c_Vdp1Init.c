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
typedef  int /*<<< orphan*/  Vdp1 ;
struct TYPE_2__ {int disptoggle; } ;

/* Variables and functions */
 void* T1MemoryInit (int) ; 
 TYPE_1__ Vdp1External ; 
 int /*<<< orphan*/ * Vdp1FrameBuffer ; 
 int /*<<< orphan*/ * Vdp1Ram ; 
 int /*<<< orphan*/ * Vdp1Regs ; 
 scalar_t__ malloc (int) ; 

int Vdp1Init(void) {
   if ((Vdp1Regs = (Vdp1 *) malloc(sizeof(Vdp1))) == NULL)
      return -1;

   if ((Vdp1Ram = T1MemoryInit(0x80000)) == NULL)
      return -1;

   // Allocate enough memory for two frames
   if ((Vdp1FrameBuffer = T1MemoryInit(0x80000)) == NULL)
      return -1;

   Vdp1External.disptoggle = 1;

   return 0;
}