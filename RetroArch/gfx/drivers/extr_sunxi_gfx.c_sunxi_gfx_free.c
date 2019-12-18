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
struct sunxi_video {int keep_vsync; int /*<<< orphan*/  sunxi_disp; struct sunxi_video* pages; int /*<<< orphan*/  vsync_condition; int /*<<< orphan*/  pending_mutex; int /*<<< orphan*/  vsync_thread; int /*<<< orphan*/  menu_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sunxi_video*) ; 
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sthread_join (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_disp_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_restore_console (struct sunxi_video*) ; 

__attribute__((used)) static void sunxi_gfx_free(void *data)
{
   struct sunxi_video *_dispvars = (struct sunxi_video*)data;

   /* Stop the vsync thread and wait for it to join. */
   /* When menu is active, vsync thread has already been stopped. */
   if (!_dispvars->menu_active)
   {
      _dispvars->keep_vsync = false;
      sthread_join(_dispvars->vsync_thread);
   }

   slock_free(_dispvars->pending_mutex);
   scond_free(_dispvars->vsync_condition);

   free(_dispvars->pages);

   /* Restore text console contents and reactivate cursor blinking. */
   sunxi_restore_console(_dispvars);

   sunxi_disp_close(_dispvars->sunxi_disp);
   free(_dispvars);
}