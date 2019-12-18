#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  RowPitch; } ;
struct TYPE_10__ {int Offset; TYPE_2__ Footprint; } ;
struct TYPE_8__ {int /*<<< orphan*/  Format; } ;
struct TYPE_11__ {int dirty; int /*<<< orphan*/  upload_buffer; TYPE_3__ layout; TYPE_1__ desc; } ;
typedef  TYPE_4__ d3d12_texture_t ;
struct TYPE_12__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  DXGI_FORMAT ;
typedef  TYPE_5__ D3D12_RANGE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12Map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,void**) ; 
 int /*<<< orphan*/  D3D12Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dxgi_copy (int,int,int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void d3d12_update_texture(
      int              width,
      int              height,
      int              pitch,
      DXGI_FORMAT      format,
      const void*      data,
      d3d12_texture_t* texture)
{
   uint8_t*    dst;
   D3D12_RANGE read_range = { 0, 0 };

   if (!texture || !texture->upload_buffer)
      return;

   D3D12Map(texture->upload_buffer, 0, &read_range, (void**)&dst);

   dxgi_copy(
         width, height, format, pitch, data, texture->desc.Format,
         texture->layout.Footprint.RowPitch, dst + texture->layout.Offset);

   D3D12Unmap(texture->upload_buffer, 0, NULL);

   texture->dirty = true;
}