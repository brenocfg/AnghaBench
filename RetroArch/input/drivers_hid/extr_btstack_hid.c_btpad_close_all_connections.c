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
 int /*<<< orphan*/  CFRunLoopGetCurrent () ; 
 int /*<<< orphan*/  CFRunLoopStop (int /*<<< orphan*/ ) ; 
 unsigned int MAX_USERS ; 
 int /*<<< orphan*/  btpad_close_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_connections ; 

__attribute__((used)) static void btpad_close_all_connections(void)
{
   unsigned i;

   for (i = 0; i < MAX_USERS; i ++)
      btpad_close_connection(&g_connections[i]);

#ifdef __APPLE__
   CFRunLoopStop(CFRunLoopGetCurrent());
#endif
}