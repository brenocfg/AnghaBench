#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int member_3; int member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int Count; } ;
struct TYPE_7__ {int Height; int DepthOrArraySize; int MipLevels; int /*<<< orphan*/  Layout; TYPE_1__ SampleDesc; int /*<<< orphan*/  Width; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ D3D12_RESOURCE_DESC ;
typedef  TYPE_3__ D3D12_HEAP_PROPERTIES ;
typedef  int /*<<< orphan*/  D3D12_GPU_VIRTUAL_ADDRESS ;
typedef  int /*<<< orphan*/  D3D12Resource ;
typedef  int /*<<< orphan*/  D3D12Device ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12CreateCommittedResource (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D12GetGPUVirtualAddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D12_CPU_PAGE_PROPERTY_UNKNOWN ; 
 int /*<<< orphan*/  D3D12_HEAP_FLAG_NONE ; 
 int /*<<< orphan*/  D3D12_HEAP_TYPE_UPLOAD ; 
 int /*<<< orphan*/  D3D12_MEMORY_POOL_UNKNOWN ; 
 int /*<<< orphan*/  D3D12_RESOURCE_DIMENSION_BUFFER ; 
 int /*<<< orphan*/  D3D12_RESOURCE_STATE_GENERIC_READ ; 
 int /*<<< orphan*/  D3D12_TEXTURE_LAYOUT_ROW_MAJOR ; 

D3D12_GPU_VIRTUAL_ADDRESS
d3d12_create_buffer(D3D12Device device, UINT size_in_bytes, D3D12Resource* buffer)
{
   D3D12_HEAP_PROPERTIES heap_props    = { D3D12_HEAP_TYPE_UPLOAD, D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
                                        D3D12_MEMORY_POOL_UNKNOWN, 1, 1 };
   D3D12_RESOURCE_DESC   resource_desc = { D3D12_RESOURCE_DIMENSION_BUFFER };

   resource_desc.Width            = size_in_bytes;
   resource_desc.Height           = 1;
   resource_desc.DepthOrArraySize = 1;
   resource_desc.MipLevels        = 1;
   resource_desc.SampleDesc.Count = 1;
   resource_desc.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

   D3D12CreateCommittedResource(
         device, (D3D12_HEAP_PROPERTIES*)&heap_props, D3D12_HEAP_FLAG_NONE, &resource_desc,
         D3D12_RESOURCE_STATE_GENERIC_READ, NULL, buffer);

   return D3D12GetGPUVirtualAddress(*buffer);
}