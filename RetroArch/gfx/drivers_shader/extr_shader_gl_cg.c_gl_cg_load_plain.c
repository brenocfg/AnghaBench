#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct video_shader {int passes; TYPE_2__* pass; } ;
struct shader_program_info {char const* combined; int is_file; } ;
struct TYPE_7__ {struct video_shader* shader; int /*<<< orphan*/ * prg; } ;
typedef  TYPE_3__ cg_shader_data_t ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
struct TYPE_6__ {TYPE_1__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  gl_cg_compile_program (void*,int,int /*<<< orphan*/ *,struct shader_program_info*) ; 
 int /*<<< orphan*/  gl_cg_load_stock (TYPE_3__*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  video_shader_resolve_parameters (int /*<<< orphan*/ *,struct video_shader*) ; 

__attribute__((used)) static bool gl_cg_load_plain(void *data, const char *path)
{
   cg_shader_data_t *cg = (cg_shader_data_t*)data;

   if (!gl_cg_load_stock(cg))
      return false;

   cg->shader = (struct video_shader*)
      calloc(1, sizeof(*cg->shader));
   if (!cg->shader)
      return false;

   cg->shader->passes = 1;

   if (string_is_empty(path))
   {
      RARCH_LOG("[CG]: Loading stock Cg file.\n");
      cg->prg[1] = cg->prg[0];
   }
   else
   {
      struct shader_program_info program_info;

      program_info.combined = path;
      program_info.is_file  = true;

      RARCH_LOG("[CG]: Loading Cg file: %s\n", path);
      strlcpy(cg->shader->pass[0].source.path, path,
            sizeof(cg->shader->pass[0].source.path));
      if (!gl_cg_compile_program(data, 1, &cg->prg[1], &program_info))
         return false;
   }

   video_shader_resolve_parameters(NULL, cg->shader);
   return true;
}