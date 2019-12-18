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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int _xgetbv (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static uint64_t xgetbv_x86(uint32_t idx)
{
#if defined(__GNUC__)
   uint32_t eax, edx;
   __asm__ volatile (
         /* Older GCC versions (Apple's GCC for example) do
          * not understand xgetbv instruction.
          * Stamp out the machine code directly.
          */
         ".byte 0x0f, 0x01, 0xd0\n"
         : "=a"(eax), "=d"(edx) : "c"(idx));
   return ((uint64_t)edx << 32) | eax;
#elif _MSC_FULL_VER >= 160040219
   /* Intrinsic only works on 2010 SP1 and above. */
   return _xgetbv(idx);
#else
   printf("Unknown compiler. Cannot check xgetbv bits.\n");
   return 0;
#endif
}