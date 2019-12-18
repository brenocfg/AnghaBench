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
 int /*<<< orphan*/  stub1 () ; 

__attribute__((weak))
void __fini(void)
{
   extern void (*const __DTOR_LIST__)(void);
   extern void (*const __DTOR_END__)(void);

   void (*const *dtor)(void) = &__DTOR_LIST__;
   while (dtor < &__DTOR_END__) {
      (*dtor++)();
   }
}