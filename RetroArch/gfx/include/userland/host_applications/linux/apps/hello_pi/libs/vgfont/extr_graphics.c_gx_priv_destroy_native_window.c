#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  element; } ;
struct TYPE_7__ {TYPE_1__ egl_win; } ;
struct TYPE_8__ {TYPE_2__ native_window; } ;
struct TYPE_9__ {int /*<<< orphan*/  screen_id; TYPE_3__ u; } ;
typedef  TYPE_4__ GRAPHICS_RESOURCE_HANDLE_TABLE_T ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  gx_priv_release_screen (int /*<<< orphan*/ ) ; 
 int vc_dispmanx_element_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_start (int /*<<< orphan*/ ) ; 
 int vc_dispmanx_update_submit_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

void
gx_priv_destroy_native_window(GRAPHICS_RESOURCE_HANDLE_TABLE_T *res)
{
   DISPMANX_UPDATE_HANDLE_T current_update;

   if((current_update = vc_dispmanx_update_start(0)) != 0)
   {
      int ret = vc_dispmanx_element_remove(current_update, res->u.native_window.egl_win.element);
      vcos_assert(ret == 0);
      ret = vc_dispmanx_update_submit_sync(current_update);
      vcos_assert(ret == 0);
   }

   gx_priv_release_screen(res->screen_id);
}