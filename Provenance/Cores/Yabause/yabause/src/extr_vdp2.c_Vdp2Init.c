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
typedef  int /*<<< orphan*/  Vdp2 ;

/* Variables and functions */
 int /*<<< orphan*/ * T1MemoryInit (int) ; 
 int /*<<< orphan*/ * T2MemoryInit (int) ; 
 int /*<<< orphan*/ * Vdp2ColorRam ; 
 int /*<<< orphan*/ * Vdp2Ram ; 
 int /*<<< orphan*/ * Vdp2Regs ; 
 int /*<<< orphan*/  Vdp2Reset () ; 
 scalar_t__ calloc (int,int) ; 

int Vdp2Init(void) {
   if ((Vdp2Regs = (Vdp2 *) calloc(1, sizeof(Vdp2))) == NULL)
      return -1;

   if ((Vdp2Ram = T1MemoryInit(0x80000)) == NULL)
      return -1;

   if ((Vdp2ColorRam = T2MemoryInit(0x1000)) == NULL)
      return -1;

   Vdp2Reset();
   return 0;
}