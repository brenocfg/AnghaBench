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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __real_free (void*) ; 
 int /*<<< orphan*/  _mem2_free (void*) ; 

__attribute__ ((used)) void __wrap_free(void *p)
{
   if (!p)
      return;

   if (((uint32_t)p & 0x10000000) != 0)
      _mem2_free(p);
   else
      __real_free(p);
}