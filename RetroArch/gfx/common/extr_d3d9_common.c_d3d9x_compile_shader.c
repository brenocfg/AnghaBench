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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPD3DXINCLUDE ;
typedef  int /*<<< orphan*/  LPD3DXCONSTANTTABLE ;
typedef  int /*<<< orphan*/  LPD3DXBUFFER ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DXMACRO ;

/* Variables and functions */
 scalar_t__ D3D9CompileShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool d3d9x_compile_shader(
      const char *src,
      unsigned src_data_len,
      const void *pdefines,
      void *pinclude,
      const char *pfunctionname,
      const char *pprofile,
      unsigned flags,
      void *ppshader,
      void *pperrormsgs,
      void *ppconstanttable)
{
#if defined(HAVE_D3DX)
   if (D3D9CompileShader)
      if (D3D9CompileShader(
               (LPCTSTR)src,
               (UINT)src_data_len,
               (const D3DXMACRO*)pdefines,
               (LPD3DXINCLUDE)pinclude,
               (LPCSTR)pfunctionname,
               (LPCSTR)pprofile,
               (DWORD)flags,
               (LPD3DXBUFFER*)ppshader,
               (LPD3DXBUFFER*)pperrormsgs,
               (LPD3DXCONSTANTTABLE*)ppconstanttable) >= 0)
         return true;
#endif
   return false;
}