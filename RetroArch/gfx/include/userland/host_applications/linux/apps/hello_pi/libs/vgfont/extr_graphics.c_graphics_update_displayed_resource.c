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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  gx_priv_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t graphics_update_displayed_resource(GRAPHICS_RESOURCE_HANDLE res,
                                           const uint32_t x_offset,
                                           const uint32_t y_offset,
                                           const uint32_t width,
                                           const uint32_t height )
{
   GX_CLIENT_STATE_T save;
   gx_priv_save(&save, res);

   gx_priv_flush(res);

   gx_priv_restore(&save);

   return 0;
}