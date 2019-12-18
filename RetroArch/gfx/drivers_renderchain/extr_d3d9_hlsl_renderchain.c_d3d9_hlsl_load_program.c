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
struct shader_pass {int /*<<< orphan*/  vprg; int /*<<< orphan*/  fprg; int /*<<< orphan*/  vtable; int /*<<< orphan*/  ftable; } ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;
typedef  int /*<<< orphan*/  ID3DXBuffer ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  d3d9_create_pixel_shader (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void**) ; 
 int /*<<< orphan*/  d3d9_create_vertex_shader (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void**) ; 
 int /*<<< orphan*/  d3d9x_buffer_release (void*) ; 
 int /*<<< orphan*/  d3d9x_compile_shader (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ d3d9x_get_buffer_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static bool d3d9_hlsl_load_program(
      LPDIRECT3DDEVICE9 dev,
      struct shader_pass *pass,
      const char *prog)
{
   ID3DXBuffer *listing_f                    = NULL;
   ID3DXBuffer *listing_v                    = NULL;
   ID3DXBuffer *code_f                       = NULL;
   ID3DXBuffer *code_v                       = NULL;

   if (!d3d9x_compile_shader(prog, strlen(prog), NULL, NULL,
            "main_fragment", "ps_3_0", 0, &code_f, &listing_f,
            &pass->ftable ))
   {
      RARCH_ERR("Could not compile stock fragment shader..\n");
      goto error;
   }
   if (!d3d9x_compile_shader(prog, strlen(prog), NULL, NULL,
            "main_vertex", "vs_3_0", 0, &code_v, &listing_v,
            &pass->vtable ))
   {
      RARCH_ERR("Could not compile stock vertex shader..\n");
      goto error;
   }

   d3d9_create_pixel_shader(dev,  (const DWORD*)d3d9x_get_buffer_ptr(code_f),  (void**)&pass->fprg);
   d3d9_create_vertex_shader(dev, (const DWORD*)d3d9x_get_buffer_ptr(code_v), (void**)&pass->vprg);
   d3d9x_buffer_release((void*)code_f);
   d3d9x_buffer_release((void*)code_v);

   return true;

error:
   RARCH_ERR("Cg/HLSL error:\n");
   if (listing_f)
      RARCH_ERR("Fragment:\n%s\n", (char*)d3d9x_get_buffer_ptr(listing_f));
   if (listing_v)
      RARCH_ERR("Vertex:\n%s\n", (char*)d3d9x_get_buffer_ptr(listing_v));
   d3d9x_buffer_release((void*)listing_f);
   d3d9x_buffer_release((void*)listing_v);

   return false;
}