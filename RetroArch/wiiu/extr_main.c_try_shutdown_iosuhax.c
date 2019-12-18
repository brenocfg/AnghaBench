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
 int /*<<< orphan*/  IOSUHAX_Close () ; 
 int /*<<< orphan*/  MCPHookClose () ; 
 int iosuhaxMount ; 
 scalar_t__ mcp_hook_fd ; 

__attribute__((used)) static void try_shutdown_iosuhax(void)
{
#ifdef HAVE_IOSUHAX
   if(!iosuhaxMount)
    return;

   if (mcp_hook_fd >= 0)
    MCPHookClose();
   else
    IOSUHAX_Close();
#endif //HAVE_IOSUHAX

   iosuhaxMount = false;
}