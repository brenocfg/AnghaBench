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
struct TYPE_10__ {float scale_x; float scale_y; void* type_y; void* type_x; } ;
struct video_shader_pass {TYPE_3__ fbo; int /*<<< orphan*/  filter; } ;
struct TYPE_12__ {unsigned int passes; TYPE_2__* pass; } ;
struct TYPE_11__ {TYPE_5__ shader; } ;
typedef  TYPE_4__ d3d9_video_t ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_8__ {float scale_y; float scale_x; scalar_t__ valid; void* type_y; void* type_x; } ;
struct TYPE_9__ {TYPE_1__ fbo; } ;

/* Variables and functions */
 unsigned int GFX_MAX_SHADERS ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_FILTER_UNSPEC ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int) ; 
 void* RARCH_SCALE_INPUT ; 
 void* RARCH_SCALE_VIEWPORT ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_shader_read_conf_preset (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * video_shader_read_preset (char const*) ; 

__attribute__((used)) static bool d3d9_init_multipass(d3d9_video_t *d3d, const char *shader_path)
{
   unsigned i;
   bool            use_extra_pass = false;
   struct video_shader_pass *pass = NULL;
   config_file_t            *conf = video_shader_read_preset(shader_path);

   if (!conf)
   {
      RARCH_ERR("[D3D9]: Failed to load preset.\n");
      return false;
   }

   memset(&d3d->shader, 0, sizeof(d3d->shader));

   if (!video_shader_read_conf_preset(conf, &d3d->shader))
   {
      config_file_free(conf);
      RARCH_ERR("[D3D9]: Failed to parse shader preset.\n");
      return false;
   }

   config_file_free(conf);

   RARCH_LOG("[D3D9]: Found %u shaders.\n", d3d->shader.passes);

   for (i = 0; i < d3d->shader.passes; i++)
   {
      if (d3d->shader.pass[i].fbo.valid)
         continue;

      d3d->shader.pass[i].fbo.scale_y = 1.0f;
      d3d->shader.pass[i].fbo.scale_x = 1.0f;
      d3d->shader.pass[i].fbo.type_x  = RARCH_SCALE_INPUT;
      d3d->shader.pass[i].fbo.type_y  = RARCH_SCALE_INPUT;
   }

   use_extra_pass       = d3d->shader.passes < GFX_MAX_SHADERS &&
      d3d->shader.pass[d3d->shader.passes - 1].fbo.valid;

   if (use_extra_pass)
   {
      d3d->shader.passes++;
      pass              = (struct video_shader_pass*)
         &d3d->shader.pass[d3d->shader.passes - 1];

      pass->fbo.scale_x = 1.0f;
      pass->fbo.scale_y = 1.0f;
      pass->fbo.type_x  = RARCH_SCALE_VIEWPORT;
      pass->fbo.type_y  = RARCH_SCALE_VIEWPORT;
      pass->filter      = RARCH_FILTER_UNSPEC;
   }
   else
   {
      pass              = (struct video_shader_pass*)
         &d3d->shader.pass[d3d->shader.passes - 1];

      pass->fbo.scale_x = 1.0f;
      pass->fbo.scale_y = 1.0f;
      pass->fbo.type_x  = RARCH_SCALE_VIEWPORT;
      pass->fbo.type_y  = RARCH_SCALE_VIEWPORT;
   }

   return true;
}