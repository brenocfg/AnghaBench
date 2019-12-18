#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  layout; int /*<<< orphan*/  gs; int /*<<< orphan*/  ps; int /*<<< orphan*/  vs; } ;
typedef  TYPE_1__ d3d10_shader_t ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int /*<<< orphan*/ * D3DBlob ;
typedef  int /*<<< orphan*/  D3D10_INPUT_ELEMENT_DESC ;
typedef  int /*<<< orphan*/  D3D10Device ;

/* Variables and functions */
 int /*<<< orphan*/  D3D10CreateGeometryShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D10CreateInputLayout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D10CreatePixelShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D10CreateVertexShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3DGetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3DGetBufferSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d_compile (char const*,size_t,scalar_t__,scalar_t__,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  d3d_compile_from_file (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ **) ; 

bool d3d10_init_shader(
      D3D10Device                     device,
      const char*                     src,
      size_t                          size,
      const void*                     src_name,
      LPCSTR                          vs_entry,
      LPCSTR                          ps_entry,
      LPCSTR                          gs_entry,
      const D3D10_INPUT_ELEMENT_DESC* input_element_descs,
      UINT                            num_elements,
      d3d10_shader_t*                 out)
{
   D3DBlob vs_code = NULL;
   D3DBlob ps_code = NULL;
   D3DBlob gs_code = NULL;

   bool success = true;

   if (!src) /* LPCWSTR filename */
   {
      if (vs_entry && !d3d_compile_from_file((LPCWSTR)src_name, vs_entry, "vs_4_0", &vs_code))
         success = false;
      if (ps_entry && !d3d_compile_from_file((LPCWSTR)src_name, ps_entry, "ps_4_0", &ps_code))
         success = false;
      if (gs_entry && !d3d_compile_from_file((LPCWSTR)src_name, gs_entry, "gs_4_0", &gs_code))
         success = false;
   }
   else /* char array */
   {
      if (vs_entry && !d3d_compile(src, size, (LPCSTR)src_name, vs_entry, "vs_4_0", &vs_code))
         success = false;
      if (ps_entry && !d3d_compile(src, size, (LPCSTR)src_name, ps_entry, "ps_4_0", &ps_code))
         success = false;
      if (gs_entry && !d3d_compile(src, size, (LPCSTR)src_name, gs_entry, "gs_4_0", &gs_code))
         success = false;
   }

   if (vs_code)
      D3D10CreateVertexShader(
            device, D3DGetBufferPointer(vs_code), D3DGetBufferSize(vs_code), &out->vs);

   if (ps_code)
      D3D10CreatePixelShader(
            device, D3DGetBufferPointer(ps_code), D3DGetBufferSize(ps_code), &out->ps);

   if (gs_code)
      D3D10CreateGeometryShader(
            device, D3DGetBufferPointer(gs_code), D3DGetBufferSize(gs_code), &out->gs);

   if (vs_code && input_element_descs)
      D3D10CreateInputLayout(
            device,
            (D3D10_INPUT_ELEMENT_DESC*)input_element_descs, num_elements, D3DGetBufferPointer(vs_code),
            D3DGetBufferSize(vs_code), &out->layout);

   Release(vs_code);
   Release(ps_code);
   Release(gs_code);

   return success;
}