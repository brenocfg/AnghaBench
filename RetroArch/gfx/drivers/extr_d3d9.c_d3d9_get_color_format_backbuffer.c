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
struct TYPE_3__ {int /*<<< orphan*/  Format; } ;
typedef  int /*<<< orphan*/  D3DFORMAT ;
typedef  TYPE_1__ D3DDISPLAYMODE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFMT_X8R8G8B8 ; 
 scalar_t__ d3d9_get_adapter_display_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  d3d9_get_rgb565_format () ; 
 int /*<<< orphan*/  g_pD3D9 ; 

__attribute__((used)) static D3DFORMAT d3d9_get_color_format_backbuffer(bool rgb32, bool windowed)
{
   D3DFORMAT fmt = D3DFMT_X8R8G8B8;
#ifdef _XBOX
   if (!rgb32)
      fmt        = d3d9_get_rgb565_format();
#else
   if (windowed)
   {
      D3DDISPLAYMODE display_mode;
      if (d3d9_get_adapter_display_mode(g_pD3D9, 0, &display_mode))
         fmt = display_mode.Format;
   }
#endif
   return fmt;
}