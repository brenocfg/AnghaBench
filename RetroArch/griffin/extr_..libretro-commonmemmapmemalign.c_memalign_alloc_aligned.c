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
 void* memalign_alloc (int,size_t) ; 

void *memalign_alloc_aligned(size_t size)
{
#if defined(__x86_64__) || defined(__LP64) || defined(__IA64__) || defined(_M_X64) || defined(_M_X64) || defined(_WIN64)
   return memalign_alloc(64, size);
#elif defined(__i386__) || defined(__i486__) || defined(__i686__) || defined(GEKKO) || defined(_M_IX86)
   return memalign_alloc(32, size);
#else
   return memalign_alloc(32, size);
#endif
}