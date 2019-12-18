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
typedef  enum video_driver_enum { ____Placeholder_video_driver_enum } video_driver_enum ;

/* Variables and functions */
#define  VIDEO_CACA 160 
#define  VIDEO_CTR 159 
#define  VIDEO_D3D10 158 
#define  VIDEO_D3D11 157 
#define  VIDEO_D3D12 156 
#define  VIDEO_D3D8 155 
#define  VIDEO_D3D9 154 
 int VIDEO_DEFAULT_DRIVER ; 
#define  VIDEO_DISPMANX 153 
#define  VIDEO_DRM 152 
#define  VIDEO_EXT 151 
#define  VIDEO_EXYNOS 150 
#define  VIDEO_FPGA 149 
#define  VIDEO_GDI 148 
#define  VIDEO_GL 147 
#define  VIDEO_GL1 146 
#define  VIDEO_GL_CORE 145 
#define  VIDEO_METAL 144 
#define  VIDEO_NULL 143 
#define  VIDEO_OMAP 142 
#define  VIDEO_PS2 141 
#define  VIDEO_PSP1 140 
#define  VIDEO_SDL 139 
#define  VIDEO_SDL2 138 
#define  VIDEO_SUNXI 137 
#define  VIDEO_SWITCH 136 
#define  VIDEO_VG 135 
#define  VIDEO_VGA 134 
#define  VIDEO_VITA2D 133 
#define  VIDEO_VULKAN 132 
#define  VIDEO_WII 131 
#define  VIDEO_WIIU 130 
#define  VIDEO_XENON360 129 
#define  VIDEO_XVIDEO 128 

const char *config_get_default_video(void)
{
   enum video_driver_enum default_driver = VIDEO_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case VIDEO_GL:
         return "gl";
      case VIDEO_GL1:
         return "gl1";
      case VIDEO_GL_CORE:
         return "glcore";
      case VIDEO_VULKAN:
         return "vulkan";
      case VIDEO_METAL:
         return "metal";
      case VIDEO_DRM:
         return "drm";
      case VIDEO_WII:
         return "gx";
      case VIDEO_WIIU:
         return "gx2";
      case VIDEO_XENON360:
         return "xenon360";
      case VIDEO_D3D8:
         return "d3d8";
      case VIDEO_D3D9:
         return "d3d9";
      case VIDEO_D3D10:
         return "d3d10";
      case VIDEO_D3D11:
         return "d3d11";
      case VIDEO_D3D12:
         return "d3d12";
      case VIDEO_PSP1:
         return "psp1";
      case VIDEO_PS2:
         return "ps2";
      case VIDEO_VITA2D:
         return "vita2d";
      case VIDEO_CTR:
         return "ctr";
      case VIDEO_SWITCH:
         return "switch";
      case VIDEO_XVIDEO:
         return "xvideo";
      case VIDEO_SDL:
         return "sdl";
      case VIDEO_SDL2:
         return "sdl2";
      case VIDEO_EXT:
         return "ext";
      case VIDEO_VG:
         return "vg";
      case VIDEO_OMAP:
         return "omap";
      case VIDEO_EXYNOS:
         return "exynos";
      case VIDEO_DISPMANX:
         return "dispmanx";
      case VIDEO_SUNXI:
         return "sunxi";
      case VIDEO_CACA:
         return "caca";
      case VIDEO_GDI:
         return "gdi";
      case VIDEO_VGA:
         return "vga";
      case VIDEO_FPGA:
         return "fpga";
      case VIDEO_NULL:
         break;
   }

   return "null";
}