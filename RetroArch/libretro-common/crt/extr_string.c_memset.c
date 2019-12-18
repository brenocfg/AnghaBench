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

void *memset(void *dst, int val, size_t count)
{
   void *start = dst;

#if defined(_M_IA64) || defined (_M_AMD64) || defined(_M_ALPHA) || defined (_M_PPC)
   extern void RtlFillMemory(void *, size_t count, char);

   RtlFillMemory(dst, count, (char)val);
#else
   while (count--)
   {
      *(char*)dst = (char)val;
      dst = (char*)dst + 1;
   }
#endif

   return start;
}