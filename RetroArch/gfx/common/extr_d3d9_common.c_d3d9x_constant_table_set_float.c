#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* lpVtbl; } ;
struct TYPE_4__ {scalar_t__ (* SetFloat ) (TYPE_2__*,scalar_t__,scalar_t__,float) ;} ;
typedef  scalar_t__ LPDIRECT3DDEVICE9 ;
typedef  TYPE_2__* LPD3DXCONSTANTTABLE ;
typedef  scalar_t__ D3DXHANDLE ;

/* Variables and functions */
 scalar_t__ D3D_OK ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__,scalar_t__,float) ; 

const bool d3d9x_constant_table_set_float(void *p,
      void *a, void *b, float val)
{
#if defined(HAVE_D3DX)
   LPDIRECT3DDEVICE9    dev     = (LPDIRECT3DDEVICE9)a;
   D3DXHANDLE        handle     = (D3DXHANDLE)b;
   LPD3DXCONSTANTTABLE consttbl = (LPD3DXCONSTANTTABLE)p;
   if (consttbl && dev && handle &&
         consttbl->lpVtbl->SetFloat(
            consttbl, dev, handle, val) == D3D_OK)
      return true;
#endif
   return false;
}