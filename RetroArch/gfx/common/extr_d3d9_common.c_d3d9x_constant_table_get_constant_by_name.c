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
struct TYPE_4__ {scalar_t__ (* GetConstantByName ) (TYPE_2__*,scalar_t__,scalar_t__) ;} ;
typedef  TYPE_2__* LPD3DXCONSTANTTABLE ;
typedef  scalar_t__ LPCSTR ;
typedef  scalar_t__ D3DXHANDLE ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_2__*,scalar_t__,scalar_t__) ; 

void *d3d9x_constant_table_get_constant_by_name(void *_tbl,
      void *_handle, void *_name)
{
#if defined(HAVE_D3DX)
   D3DXHANDLE        handle     = (D3DXHANDLE)_handle;
   LPD3DXCONSTANTTABLE consttbl = (LPD3DXCONSTANTTABLE)_tbl;
   LPCSTR              name     = (LPCSTR)_name;
   if (consttbl && handle && name)
      return (void*)consttbl->lpVtbl->GetConstantByName(consttbl,
            handle, name);
#endif
   return NULL;
}