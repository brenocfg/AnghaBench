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
 int /*<<< orphan*/  T1MemoryDeInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Vdp1FrameBuffer ; 
 int /*<<< orphan*/ * Vdp1Ram ; 
 int /*<<< orphan*/ * Vdp1Regs ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void Vdp1DeInit(void) {
   if (Vdp1Regs)
      free(Vdp1Regs);
   Vdp1Regs = NULL;

   if (Vdp1Ram)
      T1MemoryDeInit(Vdp1Ram);
   Vdp1Ram = NULL;

   if (Vdp1FrameBuffer)
      T1MemoryDeInit(Vdp1FrameBuffer);
   Vdp1FrameBuffer = NULL;
}