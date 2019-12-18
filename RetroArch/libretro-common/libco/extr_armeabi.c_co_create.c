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
typedef  uintptr_t uint32_t ;
typedef  scalar_t__ cothread_t ;

/* Variables and functions */
 scalar_t__ memalign (int,unsigned int) ; 
 scalar_t__ posix_memalign (scalar_t__*,int,unsigned int) ; 

cothread_t co_create(unsigned int size, void (*entrypoint)(void))
{
   size = (size + 1023) & ~1023;
   cothread_t handle = 0;
#if defined(__APPLE__) || HAVE_POSIX_MEMALIGN >= 1
   if (posix_memalign(&handle, 1024, size + 256) < 0)
      return 0;
#else
   handle = memalign(1024, size + 256);
#endif

   if (!handle)
      return handle;

   uint32_t *ptr = (uint32_t*)handle;
   /* Non-volatiles.  */
   ptr[0] = 0; /* r4  */
   ptr[1] = 0; /* r5  */
   ptr[2] = 0; /* r6  */
   ptr[3] = 0; /* r7  */
   ptr[4] = 0; /* r8  */
   ptr[5] = 0; /* r9  */
   ptr[6] = 0; /* r10 */
   ptr[7] = 0; /* r11 */
   /* Align stack to 64-bit */
   ptr[8] = (uintptr_t)ptr + size + 256 - 8; /* r13, stack pointer */
   ptr[9] = (uintptr_t)entrypoint; /* r15, PC (link register r14 gets saved here). */
   return handle;
}