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

/* Variables and functions */
 int d3d9_dylib_initialized ; 
 int /*<<< orphan*/  dylib_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_d3d9_dll ; 
 int /*<<< orphan*/ * g_d3d9x_dll ; 

void d3d9_deinitialize_symbols(void)
{
#ifdef HAVE_DYNAMIC_D3D
   if (g_d3d9_dll)
      dylib_close(g_d3d9_dll);
#ifdef HAVE_D3DX
   if (g_d3d9x_dll)
      dylib_close(g_d3d9x_dll);
   g_d3d9x_dll        = NULL;
#endif
   g_d3d9_dll         = NULL;

   d3d9_dylib_initialized = false;
#endif
}