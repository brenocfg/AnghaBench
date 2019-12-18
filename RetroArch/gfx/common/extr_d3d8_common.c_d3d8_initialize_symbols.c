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
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;
typedef  scalar_t__ D3DXCreateFontIndirect_t ;
typedef  scalar_t__ D3DCreate_t ;
typedef  scalar_t__ D3DCreateTextureFromFile_t ;

/* Variables and functions */
 scalar_t__ D3DCreate ; 
 scalar_t__ D3DCreateFontIndirect ; 
 scalar_t__ D3DCreateTextureFromFile ; 
 scalar_t__ D3DXCreateFontIndirect ; 
 scalar_t__ D3DXCreateTextureFromFileExA ; 
 scalar_t__ Direct3DCreate8 ; 
 int SDKVersion ; 
 int /*<<< orphan*/  d3d8_deinitialize_symbols () ; 
 int dylib_initialized ; 
 scalar_t__ dylib_load (char*) ; 
 scalar_t__ dylib_proc (scalar_t__,char*) ; 
 scalar_t__ g_d3d8_dll ; 
 scalar_t__ g_d3d8x_dll ; 

bool d3d8_initialize_symbols(enum gfx_ctx_api api)
{
#ifdef HAVE_DYNAMIC_D3D
   if (dylib_initialized)
      return true;

#if defined(DEBUG) || defined(_DEBUG)
   g_d3d8_dll     = dylib_load("d3d8d.dll");
   if(!g_d3d8_dll)
#endif
      g_d3d8_dll  = dylib_load("d3d8.dll");

   if (!g_d3d8_dll)
      return false;
#endif

   SDKVersion               = 220;
#ifdef HAVE_DYNAMIC_D3D
   D3DCreate                = (D3DCreate_t)dylib_proc(g_d3d8_dll, "Direct3DCreate8");
#ifdef HAVE_D3DX
#ifdef UNICODE
   D3DCreateFontIndirect    = (D3DXCreateFontIndirect_t)dylib_proc(g_d3d8x_dll, "D3DXCreateFontIndirectW");
#else
   D3DCreateFontIndirect    = (D3DXCreateFontIndirect_t)dylib_proc(g_d3d8x_dll, "D3DXCreateFontIndirectA");
#endif
   D3DCreateTextureFromFile = (D3DCreateTextureFromFile_t)dylib_proc(g_d3d8x_dll, "D3DXCreateTextureFromFileExA");
#endif
#else
   D3DCreate                = Direct3DCreate8;
#ifdef HAVE_D3DX
   D3DCreateFontIndirect    = D3DXCreateFontIndirect;
   D3DCreateTextureFromFile = D3DXCreateTextureFromFileExA;
#endif
#endif

   if (!D3DCreate)
      goto error;

#ifdef _XBOX
   SDKVersion        = 0;
#endif
#ifdef HAVE_DYNAMIC_D3D
   dylib_initialized = true;
#endif

   return true;

error:
   d3d8_deinitialize_symbols();
   return false;
}