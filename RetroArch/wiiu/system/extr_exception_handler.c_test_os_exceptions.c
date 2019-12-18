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
 int /*<<< orphan*/  DCFlushRange (void*,int) ; 

void test_os_exceptions(void)
{
   /*Write to 0x00000000; causes DSI */
#if 0
   __asm__ volatile (
         "li %r3, 0 \n" \
         "stw %r3, 0(%r3) \n"
         );
   DCFlushRange((void*)0, 4);
#endif

   /*Malformed instruction, causes PROG. Doesn't seem to work. */
#if 0
   __asm__ volatile (
         ".int 0xDEADC0DE"
         );
#endif

   /* Jump to 0; causes ISI */
#if 0
   void (*testFunc)() = (void(*)())0;
   testFunc();
#endif
}