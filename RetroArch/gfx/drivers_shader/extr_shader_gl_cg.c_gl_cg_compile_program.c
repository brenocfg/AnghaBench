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
struct shader_program_info {int /*<<< orphan*/  combined; scalar_t__ is_file; } ;
struct shader_program_cg {void* vprg; void* fprg; } ;
struct TYPE_2__ {char** alias_define; int /*<<< orphan*/  cgCtx; int /*<<< orphan*/  cgVProf; int /*<<< orphan*/  cgFProf; struct shader_program_cg* prg; } ;
typedef  TYPE_1__ cg_shader_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SOURCE ; 
 int GFX_MAX_SHADERS ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char*) ; 
 void* cgCreateProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 void* cgCreateProgramFromFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  cgGLLoadProgram (void*) ; 
 int /*<<< orphan*/  cgGetError () ; 
 char* cgGetErrorString (int /*<<< orphan*/ ) ; 
 char* cgGetLastListing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static bool gl_cg_compile_program(
      void *data,
      unsigned idx,
      void *program_data,
      struct shader_program_info *program_info)
{
   const char *argv[2 + GFX_MAX_SHADERS];
   const char *list                  = NULL;
   bool ret                          = true;
   char *listing_f                   = NULL;
   char *listing_v                   = NULL;
   unsigned i, argc                  = 0;
   struct shader_program_cg *program = (struct shader_program_cg*)program_data;
   cg_shader_data_t              *cg = (cg_shader_data_t*)data;

   if (!program)
      program = &cg->prg[idx];

   argv[argc++] = "-DPARAMETER_UNIFORM";

   for (i = 0; i < GFX_MAX_SHADERS; i++)
   {
      if (*(cg->alias_define[i]))
         argv[argc++] = cg->alias_define[i];
   }

   argv[argc] = NULL;

   if (program_info->is_file)
      program->fprg = cgCreateProgramFromFile(
            cg->cgCtx, CG_SOURCE,
            program_info->combined, cg->cgFProf, "main_fragment", argv);
   else
      program->fprg = cgCreateProgram(cg->cgCtx, CG_SOURCE,
            program_info->combined, cg->cgFProf, "main_fragment", argv);

   list = cgGetLastListing(cg->cgCtx);

   if (list)
      listing_f = strdup(list);

   list = NULL;

   if (program_info->is_file)
      program->vprg = cgCreateProgramFromFile(
            cg->cgCtx, CG_SOURCE,
            program_info->combined, cg->cgVProf, "main_vertex", argv);
   else
      program->vprg = cgCreateProgram(cg->cgCtx, CG_SOURCE,
            program_info->combined, cg->cgVProf, "main_vertex", argv);

   list = cgGetLastListing(cg->cgCtx);

   if (list)
      listing_v = strdup(list);

   if (!program->fprg || !program->vprg)
   {
      RARCH_ERR("CG error: %s\n", cgGetErrorString(cgGetError()));
      if (listing_f)
         RARCH_ERR("Fragment:\n%s\n", listing_f);
      else if (listing_v)
         RARCH_ERR("Vertex:\n%s\n", listing_v);

      ret = false;
      goto end;
   }

   cgGLLoadProgram(program->fprg);
   cgGLLoadProgram(program->vprg);

end:
   free(listing_f);
   free(listing_v);
   return ret;
}