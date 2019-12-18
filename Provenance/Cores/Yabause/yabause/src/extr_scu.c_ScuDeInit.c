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
 int /*<<< orphan*/ * ScuBP ; 
 int /*<<< orphan*/ * ScuDsp ; 
 int /*<<< orphan*/ * ScuRegs ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void ScuDeInit(void) {
   if (ScuRegs)
      free(ScuRegs);
   ScuRegs = NULL;

   if (ScuDsp)
      free(ScuDsp);
   ScuDsp = NULL;

   if (ScuBP)
      free(ScuBP);
   ScuBP = NULL;
}