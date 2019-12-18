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
typedef  uintptr_t uint64_t ;
typedef  scalar_t__ cothread_t ;

/* Variables and functions */
 scalar_t__ memalign (int,unsigned int) ; 
 scalar_t__ posix_memalign (scalar_t__*,int,unsigned int) ; 

cothread_t co_create(unsigned int size, void (*entrypoint)(void))
{
   size = (size + 1023) & ~1023;
   cothread_t handle = 0;
#if HAVE_POSIX_MEMALIGN >= 1
   if (posix_memalign(&handle, 1024, size + 512) < 0)
      return 0;
#else
   handle = memalign(1024, size + 512);
#endif

   if (!handle)
      return handle;

   uint64_t *ptr = (uint64_t*)handle;
   /* Non-volatiles.  */
   ptr[0]  = 0; /* x8  */
   ptr[1]  = 0; /* x9  */
   ptr[2]  = 0; /* x10 */
   ptr[3]  = 0; /* x11 */
   ptr[4]  = 0; /* x12 */
   ptr[5]  = 0; /* x13 */
   ptr[6]  = 0; /* x14 */
   ptr[7]  = 0; /* x15 */
   ptr[8]  = 0; /* x18 */
   ptr[9]  = 0; /* x19 */
   ptr[10] = 0; /* x20 */
   ptr[11] = 0; /* x21 */
   ptr[12] = 0; /* x22 */
   ptr[13] = 0; /* x23 */
   ptr[14] = 0; /* x24 */
   ptr[15] = 0; /* x25 */
   ptr[16] = 0; /* x26 */
   ptr[17] = 0; /* x27 */
   ptr[18] = 0; /* x28 */
   ptr[20] = (uintptr_t)ptr + size + 512 - 16; /* x30, stack pointer */
   ptr[19] = ptr[20]; /* x29, frame pointer */
   ptr[21] = (uintptr_t)entrypoint; /* PC (link register x31 gets saved here). */
   return handle;
}