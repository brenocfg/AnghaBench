#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* prg; } ;
typedef  TYPE_2__ cg_shader_data_t ;
struct TYPE_3__ {int /*<<< orphan*/  vprg; void* lut_tex; void* vertex; void* color; void* tex; } ;
typedef  void* CGparameter ;

/* Variables and functions */
 scalar_t__ CG_IN ; 
 int /*<<< orphan*/  CG_PROGRAM ; 
 scalar_t__ CG_VARYING ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*,unsigned int) ; 
 void* cgGetFirstParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cgGetNamedParameter (int /*<<< orphan*/ ,char*) ; 
 void* cgGetNextParameter (void*) ; 
 scalar_t__ cgGetParameterDirection (void*) ; 
 char* cgGetParameterSemantic (void*) ; 
 scalar_t__ cgGetParameterVariability (void*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static void gl_cg_set_program_base_attrib(void *data, unsigned i)
{
   cg_shader_data_t      *cg = (cg_shader_data_t*)data;
   CGparameter         param = cgGetFirstParameter(
         cg->prg[i].vprg, CG_PROGRAM);

   for (; param; param = cgGetNextParameter(param))
   {
      const char *semantic = NULL;
      if (     (cgGetParameterDirection(param)   != CG_IN)
            || (cgGetParameterVariability(param) != CG_VARYING))
         continue;

      semantic = cgGetParameterSemantic(param);
      if (!semantic)
         continue;

      RARCH_LOG("[CG]: Found semantic \"%s\" in prog #%u.\n", semantic, i);

      if (
            string_is_equal(semantic, "TEXCOORD") ||
            string_is_equal(semantic, "TEXCOORD0")
         )
         cg->prg[i].tex     = param;
      else if (
            string_is_equal(semantic, "COLOR") ||
            string_is_equal(semantic, "COLOR0")
            )
            cg->prg[i].color   = param;
      else if (string_is_equal(semantic, "POSITION"))
         cg->prg[i].vertex  = param;
      else if (string_is_equal(semantic, "TEXCOORD1"))
         cg->prg[i].lut_tex = param;
   }

   if (!cg->prg[i].tex)
      cg->prg[i].tex     = cgGetNamedParameter(cg->prg[i].vprg, "IN.tex_coord");
   if (!cg->prg[i].color)
      cg->prg[i].color   = cgGetNamedParameter(cg->prg[i].vprg, "IN.color");
   if (!cg->prg[i].vertex)
      cg->prg[i].vertex  = cgGetNamedParameter(cg->prg[i].vprg, "IN.vertex_coord");
   if (!cg->prg[i].lut_tex)
      cg->prg[i].lut_tex = cgGetNamedParameter(cg->prg[i].vprg, "IN.lut_tex_coord");
}