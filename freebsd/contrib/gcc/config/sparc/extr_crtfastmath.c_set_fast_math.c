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
 unsigned int FPRS_NS ; 

__attribute__((used)) static void __attribute__((constructor))
set_fast_math (void)
{
  unsigned int fsr;

  /* This works for the 64-bit case because, even if 32-bit ld/st of
     the fsr register modified the upper 32-bit, the only thing up there
     are the 3 other condition codes which are "do not care" at the time
     that this runs.  */

  __asm__("st %%fsr, %0"
	  : "=m" (fsr));

  fsr |= FPRS_NS;

  __asm__("ld %0, %%fsr"
	  : : "m" (fsr));
}