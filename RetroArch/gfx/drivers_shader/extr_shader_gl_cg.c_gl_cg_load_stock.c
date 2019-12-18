#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct shader_program_info {int is_file; int /*<<< orphan*/  combined; } ;
struct TYPE_2__ {int /*<<< orphan*/ * prg; } ;
typedef  TYPE_1__ cg_shader_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  gl_cg_compile_program (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct shader_program_info*) ; 
 int /*<<< orphan*/  gl_cg_set_program_base_attrib (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stock_cg_gl_program ; 

__attribute__((used)) static bool gl_cg_load_stock(void *data)
{
   struct shader_program_info program_info;
   cg_shader_data_t *cg  = (cg_shader_data_t*)data;

   program_info.combined = stock_cg_gl_program;
   program_info.is_file  = false;

   if (!gl_cg_compile_program(data, 0, &cg->prg[0], &program_info))
      goto error;

   gl_cg_set_program_base_attrib(data, 0);

   return true;

error:
   RARCH_ERR("Failed to compile passthrough shader, is something wrong with your environment?\n");
   return false;
}