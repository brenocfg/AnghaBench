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
 int IOSUHAX_Open (int /*<<< orphan*/ *) ; 
 int MCPHookOpen () ; 

__attribute__((used)) static bool try_init_iosuhax(void)
{
#ifdef HAVE_IOSUHAX
   int result = IOSUHAX_Open(NULL);
   if(result < 0)
      result = MCPHookOpen();

   return (result < 0) ? false : true;
#else //don't HAVE_IOSUHAX
   return false;
#endif
}