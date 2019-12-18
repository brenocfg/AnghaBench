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
 scalar_t__ malloc (size_t) ; 

void *memalign_alloc(size_t boundary, size_t size)
{
   void **place   = NULL;
   uintptr_t addr = 0;
   void *ptr      = (void*)malloc(boundary + size + sizeof(uintptr_t));
   if (!ptr)
      return NULL;

   addr           = ((uintptr_t)ptr + sizeof(uintptr_t) + boundary)
      & ~(boundary - 1);
   place          = (void**)addr;
   place[-1]      = ptr;

   return (void*)addr;
}