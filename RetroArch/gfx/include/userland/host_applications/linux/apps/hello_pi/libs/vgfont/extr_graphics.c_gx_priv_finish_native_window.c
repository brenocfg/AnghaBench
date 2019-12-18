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
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE_TABLE_T ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_dispmanx_update_submit_sync (int /*<<< orphan*/ ) ; 

void gx_priv_finish_native_window(GRAPHICS_RESOURCE_HANDLE_TABLE_T *res,
                                  void *current_update)
{
   vc_dispmanx_update_submit_sync((DISPMANX_UPDATE_HANDLE_T)current_update);
}