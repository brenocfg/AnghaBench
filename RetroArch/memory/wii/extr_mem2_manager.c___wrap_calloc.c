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
 void* __real_calloc (size_t,size_t) ; 
 void* _mem2_calloc (size_t,size_t) ; 

__attribute__ ((used)) void *__wrap_calloc(size_t n, size_t size)
{
   void *p = __real_calloc(n, size);
   if (p != 0)
      return p;
   return _mem2_calloc(n, size);
}