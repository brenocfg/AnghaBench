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
struct TYPE_4__ {int /*<<< orphan*/  (* SetMatrix ) (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/  const*) ;} ;
typedef  scalar_t__ LPDIRECT3DDEVICE9 ;
typedef  TYPE_2__* LPD3DXCONSTANTTABLE ;
typedef  int /*<<< orphan*/  D3DXMATRIX ;
typedef  scalar_t__ D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/  const*) ; 

void d3d9x_constant_table_set_matrix(LPDIRECT3DDEVICE9 dev,
      void *p,
      void *data, const void *_matrix)
{
#if defined(HAVE_D3DX)
   LPD3DXCONSTANTTABLE consttbl = (LPD3DXCONSTANTTABLE)p;
   D3DXHANDLE        handle     = (D3DXHANDLE)data;
   const D3DXMATRIX  *matrix    = (const D3DXMATRIX*)_matrix;
   if (consttbl && dev && handle)
      consttbl->lpVtbl->SetMatrix(consttbl, dev, handle, matrix);
#endif
}