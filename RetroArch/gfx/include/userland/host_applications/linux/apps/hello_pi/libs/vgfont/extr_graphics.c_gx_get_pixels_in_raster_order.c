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
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  GX_RASTER_ORDER_T ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  gx_priv_get_pixels (int /*<<< orphan*/  const,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

VCOS_STATUS_T gx_get_pixels_in_raster_order(const GRAPHICS_RESOURCE_HANDLE res,
                                            void **pixels,
                                            GX_RASTER_ORDER_T raster_order)
{
   VCOS_STATUS_T status = VCOS_SUCCESS;
   GX_CLIENT_STATE_T save;
   gx_priv_save(&save, res);

   status = gx_priv_get_pixels(res, pixels, raster_order);

   gx_priv_restore(&save);
   return status;
}