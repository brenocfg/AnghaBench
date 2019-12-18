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
typedef  scalar_t__ D3D9XCreateFontIndirect_t ;
typedef  scalar_t__ D3D9Create_t ;
typedef  scalar_t__ D3D9CreateTextureFromFile_t ;
typedef  scalar_t__ D3D9CompileShader_t ;
typedef  scalar_t__ D3D9CompileShaderFromFile_t ;

/* Variables and functions */
 scalar_t__ D3D9CompileShader ; 
 scalar_t__ D3D9CompileShaderFromFile ; 
 scalar_t__ D3D9Create ; 
 scalar_t__ D3D9CreateFontIndirect ; 
 scalar_t__ D3D9CreateTextureFromFile ; 
 scalar_t__ D3DXCompileShader ; 
 scalar_t__ D3DXCompileShaderFromFile ; 
 scalar_t__ D3DXCreateFontIndirect ; 
 scalar_t__ D3DXCreateTextureFromFileExA ; 
 scalar_t__ Direct3DCreate9 ; 
 int d3d9_SDKVersion ; 
 int /*<<< orphan*/  d3d9_deinitialize_symbols () ; 
 int d3d9_dylib_initialized ; 
 scalar_t__ dylib_load (char*) ; 
 scalar_t__ dylib_load_d3d9x () ; 
 scalar_t__ dylib_proc (scalar_t__,char*) ; 
 scalar_t__ g_d3d9_dll ; 
 scalar_t__ g_d3d9x_dll ; 

bool d3d9_initialize_symbols(enum gfx_ctx_api api)
{
#ifdef HAVE_DYNAMIC_D3D
   if (d3d9_dylib_initialized)
      return true;

#if defined(DEBUG) || defined(_DEBUG)
   g_d3d9_dll     = dylib_load("d3d9d.dll");
   if(!g_d3d9_dll)
#endif
      g_d3d9_dll  = dylib_load("d3d9.dll");
#ifdef HAVE_D3DX
   g_d3d9x_dll    = dylib_load_d3d9x();

   if (!g_d3d9x_dll)
      return false;
#endif

   if (!g_d3d9_dll)
      return false;
#endif

   d3d9_SDKVersion            = 31;
#ifdef HAVE_DYNAMIC_D3D
   D3D9Create                 = (D3D9Create_t)dylib_proc(g_d3d9_dll, "Direct3DCreate9");
#ifdef HAVE_D3DX
   D3D9CompileShaderFromFile  = (D3D9CompileShaderFromFile_t)dylib_proc(g_d3d9x_dll, "D3DXCompileShaderFromFile");
   D3D9CompileShader          = (D3D9CompileShader_t)dylib_proc(g_d3d9x_dll, "D3DXCompileShader");
#ifdef UNICODE
   D3D9CreateFontIndirect     = (D3D9XCreateFontIndirect_t)dylib_proc(g_d3d9x_dll, "D3DXCreateFontIndirectW");
#else
   D3D9CreateFontIndirect     = (D3D9XCreateFontIndirect_t)dylib_proc(g_d3d9x_dll, "D3DXCreateFontIndirectA");
#endif
   D3D9CreateTextureFromFile  = (D3D9CreateTextureFromFile_t)dylib_proc(g_d3d9x_dll, "D3DXCreateTextureFromFileExA");
#endif
#else
   D3D9Create                 = Direct3DCreate9;
#ifdef HAVE_D3DX
   D3D9CompileShaderFromFile  = D3DXCompileShaderFromFile;
   D3D9CompileShader          = D3DXCompileShader;
   D3D9CreateFontIndirect     = D3DXCreateFontIndirect;
   D3D9CreateTextureFromFile  = D3DXCreateTextureFromFileExA;
#endif
#endif

   if (!D3D9Create)
      goto error;

#ifdef _XBOX
   d3d9_SDKVersion          = 0;
#endif
#ifdef HAVE_DYNAMIC_D3D
   d3d9_dylib_initialized = true;
#endif

   return true;

error:
   d3d9_deinitialize_symbols();
   return false;
}