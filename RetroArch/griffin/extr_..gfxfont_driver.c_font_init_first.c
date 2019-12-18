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
typedef  enum font_driver_render_api { ____Placeholder_font_driver_render_api } font_driver_render_api ;

/* Variables and functions */
#define  FONT_DRIVER_RENDER_CACA 147 
#define  FONT_DRIVER_RENDER_CTR 146 
#define  FONT_DRIVER_RENDER_D3D10_API 145 
#define  FONT_DRIVER_RENDER_D3D11_API 144 
#define  FONT_DRIVER_RENDER_D3D12_API 143 
#define  FONT_DRIVER_RENDER_D3D8_API 142 
#define  FONT_DRIVER_RENDER_D3D9_API 141 
#define  FONT_DRIVER_RENDER_DONT_CARE 140 
#define  FONT_DRIVER_RENDER_GDI 139 
#define  FONT_DRIVER_RENDER_METAL_API 138 
#define  FONT_DRIVER_RENDER_OPENGL1_API 137 
#define  FONT_DRIVER_RENDER_OPENGL_API 136 
#define  FONT_DRIVER_RENDER_OPENGL_CORE_API 135 
#define  FONT_DRIVER_RENDER_PS2 134 
#define  FONT_DRIVER_RENDER_SIXEL 133 
#define  FONT_DRIVER_RENDER_SWITCH 132 
#define  FONT_DRIVER_RENDER_VGA 131 
#define  FONT_DRIVER_RENDER_VITA2D 130 
#define  FONT_DRIVER_RENDER_VULKAN_API 129 
#define  FONT_DRIVER_RENDER_WIIU 128 
 int caca_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int ctr_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int d3d10_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int d3d11_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int d3d12_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int d3d8_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int d3d9_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int gdi_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int gl1_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int gl_core_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int gl_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int metal_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int ps2_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int sixel_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int switch_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int vga_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int vita2d_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int vulkan_font_init_first (void const**,void**,void*,char const*,float,int) ; 
 int wiiu_font_init_first (void const**,void**,void*,char const*,float,int) ; 

__attribute__((used)) static bool font_init_first(
      const void **font_driver, void **font_handle,
      void *video_data, const char *font_path, float font_size,
      enum font_driver_render_api api, bool is_threaded)
{
   if (font_path && !font_path[0])
      font_path = NULL;

   switch (api)
   {
#ifdef HAVE_OPENGL1
      case FONT_DRIVER_RENDER_OPENGL1_API:
         return gl1_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_OPENGL
      case FONT_DRIVER_RENDER_OPENGL_API:
         return gl_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_OPENGL_CORE
      case FONT_DRIVER_RENDER_OPENGL_CORE_API:
         return gl_core_font_init_first(font_driver, font_handle,
                                        video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_VULKAN
      case FONT_DRIVER_RENDER_VULKAN_API:
         return vulkan_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_METAL
   case FONT_DRIVER_RENDER_METAL_API:
      return metal_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_D3D8
      case FONT_DRIVER_RENDER_D3D8_API:
         return d3d8_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_D3D9
      case FONT_DRIVER_RENDER_D3D9_API:
         return d3d9_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_D3D10
      case FONT_DRIVER_RENDER_D3D10_API:
         return d3d10_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_D3D11
      case FONT_DRIVER_RENDER_D3D11_API:
         return d3d11_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_D3D12
      case FONT_DRIVER_RENDER_D3D12_API:
         return d3d12_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_VITA2D
      case FONT_DRIVER_RENDER_VITA2D:
         return vita2d_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef PS2
      case FONT_DRIVER_RENDER_PS2:
         return ps2_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef _3DS
      case FONT_DRIVER_RENDER_CTR:
         return ctr_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef WIIU
      case FONT_DRIVER_RENDER_WIIU:
         return wiiu_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_CACA
      case FONT_DRIVER_RENDER_CACA:
         return caca_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_SIXEL
      case FONT_DRIVER_RENDER_SIXEL:
         return sixel_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_LIBNX
      case FONT_DRIVER_RENDER_SWITCH:
         return switch_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#ifdef HAVE_GDI
#if defined(_WIN32) && !defined(_XBOX) && !defined(__WINRT__)
      case FONT_DRIVER_RENDER_GDI:
         return gdi_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
#endif
#ifdef DJGPP
      case FONT_DRIVER_RENDER_VGA:
         return vga_font_init_first(font_driver, font_handle,
               video_data, font_path, font_size, is_threaded);
#endif
      case FONT_DRIVER_RENDER_DONT_CARE:
         /* TODO/FIXME - lookup graphics driver's 'API' */
         break;
      default:
         break;
   }

   return false;
}