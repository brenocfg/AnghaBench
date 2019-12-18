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
struct TYPE_4__ {void const* (* GetBufferPointer ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ ID3DXBuffer ;

/* Variables and functions */
 void const* stub1 (TYPE_2__*) ; 

const void *d3d9x_get_buffer_ptr(void *data)
{
#if defined(HAVE_D3DX)
   ID3DXBuffer *listing = (ID3DXBuffer*)data;
   if (listing)
      return listing->lpVtbl->GetBufferPointer(listing);
#endif
   return NULL;
}