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
 int /*<<< orphan*/  T2MemoryDeInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Vdp2ColorRam ; 
 int /*<<< orphan*/ * Vdp2Ram ; 
 int /*<<< orphan*/ * Vdp2Regs ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void Vdp2DeInit(void) {
   if (Vdp2Regs)
      free(Vdp2Regs);
   Vdp2Regs = NULL;

   if (Vdp2Ram)
      T1MemoryDeInit(Vdp2Ram);
   Vdp2Ram = NULL;

   if (Vdp2ColorRam)
      T2MemoryDeInit(Vdp2ColorRam);
   Vdp2ColorRam = NULL;
}