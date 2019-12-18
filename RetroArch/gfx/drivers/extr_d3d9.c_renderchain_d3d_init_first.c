#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;
struct TYPE_5__ {int /*<<< orphan*/  ident; void* (* chain_new ) () ;} ;
typedef  TYPE_1__ d3d9_renderchain_driver_t ;

/* Variables and functions */
#define  GFX_CTX_DIRECT3D9_API 131 
#define  GFX_CTX_NONE 130 
 int /*<<< orphan*/  RARCH_SHADER_CG ; 
 int /*<<< orphan*/  RARCH_SHADER_HLSL ; 
#define  cg_d3d9_renderchain 129 
#define  hlsl_d3d9_renderchain 128 
 int /*<<< orphan*/  string_is_equal (int /*<<< orphan*/ ,char*) ; 
 void* stub1 () ; 
 int /*<<< orphan*/  supported_shader_type ; 

__attribute__((used)) static bool renderchain_d3d_init_first(
      enum gfx_ctx_api api,
      const d3d9_renderchain_driver_t **renderchain_driver,
      void **renderchain_handle)
{
   switch (api)
   {
      case GFX_CTX_DIRECT3D9_API:
         {
            static const d3d9_renderchain_driver_t *renderchain_d3d_drivers[] =
            {
#if defined(_WIN32) && defined(HAVE_CG)
               &cg_d3d9_renderchain,
#endif
#if defined(_WIN32) && defined(HAVE_HLSL)
               &hlsl_d3d9_renderchain,
#endif
               NULL
            };
            unsigned i;

            for (i = 0; renderchain_d3d_drivers[i]; i++)
            {
               void *data = renderchain_d3d_drivers[i]->chain_new();

               if (!data)
                  continue;

               *renderchain_driver = renderchain_d3d_drivers[i];
               *renderchain_handle = data;

               if (string_is_equal(renderchain_d3d_drivers[i]->ident, "cg_d3d9"))
                  supported_shader_type = RARCH_SHADER_CG;
               else if (string_is_equal(renderchain_d3d_drivers[i]->ident, "hlsl_d3d9"))
                  supported_shader_type = RARCH_SHADER_HLSL;

               return true;
            }
         }
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   return false;
}