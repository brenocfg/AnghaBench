#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int Count; } ;
struct TYPE_12__ {int /*<<< orphan*/  CullMode; int /*<<< orphan*/  FillMode; } ;
struct TYPE_11__ {void* BytecodeLength; int /*<<< orphan*/ * pShaderBytecode; } ;
struct TYPE_10__ {void* BytecodeLength; int /*<<< orphan*/ * pShaderBytecode; } ;
struct TYPE_9__ {void* BytecodeLength; int /*<<< orphan*/ * pShaderBytecode; } ;
struct TYPE_14__ {int NumRenderTargets; TYPE_5__ SampleDesc; TYPE_4__ RasterizerState; int /*<<< orphan*/  SampleMask; TYPE_3__ GS; TYPE_2__ PS; TYPE_1__ VS; } ;
typedef  scalar_t__ D3DBlob ;
typedef  TYPE_6__ D3D12_GRAPHICS_PIPELINE_STATE_DESC ;
typedef  int /*<<< orphan*/  D3D12PipelineState ;
typedef  int /*<<< orphan*/  D3D12Device ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12CreateGraphicsPipelineState (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D12_CULL_MODE_NONE ; 
 int /*<<< orphan*/  D3D12_FILL_MODE_SOLID ; 
 void* D3DGetBufferPointer (scalar_t__) ; 
 void* D3DGetBufferSize (scalar_t__) ; 
 int /*<<< orphan*/  UINT_MAX ; 

bool d3d12_init_pipeline(
      D3D12Device                         device,
      D3DBlob                             vs_code,
      D3DBlob                             ps_code,
      D3DBlob                             gs_code,
      D3D12_GRAPHICS_PIPELINE_STATE_DESC* desc,
      D3D12PipelineState*                 out)
{
   if (vs_code)
   {
      desc->VS.pShaderBytecode = D3DGetBufferPointer(vs_code);
      desc->VS.BytecodeLength  = D3DGetBufferSize(vs_code);
   }
   else
   {
      desc->VS.pShaderBytecode = NULL;
      desc->VS.BytecodeLength  = 0;
   }

   if (ps_code)
   {
      desc->PS.pShaderBytecode = D3DGetBufferPointer(ps_code);
      desc->PS.BytecodeLength  = D3DGetBufferSize(ps_code);
   }
   else
   {
      desc->PS.pShaderBytecode = NULL;
      desc->PS.BytecodeLength  = 0;
   }

   if (gs_code)
   {
      desc->GS.pShaderBytecode = D3DGetBufferPointer(gs_code);
      desc->GS.BytecodeLength  = D3DGetBufferSize(gs_code);
   }
   else
   {
      desc->GS.pShaderBytecode = NULL;
      desc->GS.BytecodeLength  = 0;
   }

   desc->SampleMask               = UINT_MAX;
   desc->RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
   desc->RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
   desc->NumRenderTargets         = 1;
   desc->SampleDesc.Count         = 1;

   D3D12CreateGraphicsPipelineState(device, desc, out);

   return true;
}