#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_5__ {scalar_t__ height; } ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  TYPE_1__* GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 scalar_t__ gx_priv_resource_fill (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,TYPE_1__*) ; 

int32_t graphics_resource_fill(GRAPHICS_RESOURCE_HANDLE res,
                               uint32_t x,
                               uint32_t y,
                               uint32_t width,
                               uint32_t height,
                               uint32_t fill_colour )
{
   GX_CLIENT_STATE_T save;
   gx_priv_save(&save, res);

   VCOS_STATUS_T st = gx_priv_resource_fill(
      res,
      x, res->height-y-height,
      width, height,
      fill_colour);

   gx_priv_restore(&save);

   return st == VCOS_SUCCESS ? 0 : -1;
}