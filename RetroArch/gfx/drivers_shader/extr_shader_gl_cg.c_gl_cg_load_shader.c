#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct shader_program_info {int is_file; int /*<<< orphan*/  combined; } ;
struct TYPE_8__ {int /*<<< orphan*/ * prg; TYPE_3__* shader; } ;
typedef  TYPE_4__ cg_shader_data_t ;
struct TYPE_7__ {TYPE_2__* pass; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
struct TYPE_6__ {TYPE_1__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_cg_compile_program (void*,unsigned int,int /*<<< orphan*/ *,struct shader_program_info*) ; 

__attribute__((used)) static bool gl_cg_load_shader(void *data, unsigned i)
{
   struct shader_program_info program_info;
   cg_shader_data_t *cg  = (cg_shader_data_t*)data;

   program_info.combined = cg->shader->pass[i].source.path;
   program_info.is_file  = true;

   RARCH_LOG("[CG]: Loading Cg shader: \"%s\".\n",
         cg->shader->pass[i].source.path);

   if (!gl_cg_compile_program(data, i + 1, &cg->prg[i + 1],&program_info))
      return false;

   return true;
}