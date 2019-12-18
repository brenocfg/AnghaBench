#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* ctx_data; } ;
typedef  TYPE_2__ vk_t ;
struct TYPE_7__ {int /*<<< orphan*/  video_context_driver; } ;
struct TYPE_9__ {TYPE_1__ arrays; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  gfx_ctx_driver_t ;
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;

/* Variables and functions */
 int GFX_CTX_VULKAN_API ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/ * video_context_driver_init_first (TYPE_2__*,int /*<<< orphan*/ ,int,unsigned int,unsigned int,int,void**) ; 

__attribute__((used)) static const gfx_ctx_driver_t *vulkan_get_context(vk_t *vk)
{
   void                 *ctx_data  = NULL;
   unsigned major                  = 1;
   unsigned minor                  = 0;
   settings_t *settings            = config_get_ptr();
   enum gfx_ctx_api api            = GFX_CTX_VULKAN_API;
   const gfx_ctx_driver_t *gfx_ctx = video_context_driver_init_first(
         vk, settings->arrays.video_context_driver,
         api, major, minor, false, &ctx_data);

   if (ctx_data)
      vk->ctx_data = ctx_data;

   return gfx_ctx;
}