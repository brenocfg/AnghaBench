#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_info_t ;
typedef  int /*<<< orphan*/  d3dpp ;
struct TYPE_3__ {int /*<<< orphan*/  cur_mon_id; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ d3d8_video_t ;
typedef  scalar_t__ LPDIRECT3D8 ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  D3DPRESENT_PARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ d3d8_create () ; 
 int /*<<< orphan*/  d3d8_create_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_make_d3dpp (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ g_pD3D8 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * win32_get_window () ; 

__attribute__((used)) static bool d3d8_init_base(void *data, const video_info_t *info)
{
   D3DPRESENT_PARAMETERS d3dpp;
   HWND focus_window = NULL;
   d3d8_video_t *d3d  = (d3d8_video_t*)data;

#ifndef _XBOX
   focus_window      = win32_get_window();
#endif

   memset(&d3dpp, 0, sizeof(d3dpp));

   g_pD3D8            = (LPDIRECT3D8)d3d8_create();

   /* this needs g_pD3D created first */
   d3d8_make_d3dpp(d3d, info, &d3dpp);

   if (!g_pD3D8)
   {
      RARCH_ERR("[D3D8]: Failed to create D3D interface.\n");
      return false;
   }

   if (!d3d8_create_device(&d3d->dev, &d3dpp,
            g_pD3D8,
            focus_window,
            d3d->cur_mon_id)
      )
   {
      RARCH_ERR("[D3D8]: Failed to initialize device.\n");
      return false;
   }

   return true;
}