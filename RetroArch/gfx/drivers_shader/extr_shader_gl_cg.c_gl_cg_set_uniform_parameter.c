#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  v3; int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  v0; } ;
struct TYPE_9__ {int /*<<< orphan*/  floatv; TYPE_3__ f; } ;
struct TYPE_7__ {int type; size_t idx; char* ident; scalar_t__ add_prefix; scalar_t__ enable; } ;
struct uniform_info {int type; TYPE_4__ result; TYPE_2__ lookup; int /*<<< orphan*/  enabled; } ;
struct uniform_cg {int /*<<< orphan*/  loc; } ;
typedef  int /*<<< orphan*/  ident ;
struct TYPE_10__ {TYPE_1__* prg; } ;
typedef  TYPE_5__ cg_shader_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  fprg; int /*<<< orphan*/  vprg; } ;
typedef  int /*<<< orphan*/  CGprogram ;
typedef  int /*<<< orphan*/  CGparameter ;

/* Variables and functions */
#define  SHADER_PROGRAM_FRAGMENT 138 
#define  SHADER_PROGRAM_VERTEX 137 
#define  UNIFORM_1F 136 
#define  UNIFORM_1FV 135 
#define  UNIFORM_1I 134 
#define  UNIFORM_2F 133 
#define  UNIFORM_2FV 132 
#define  UNIFORM_3F 131 
#define  UNIFORM_3FV 130 
#define  UNIFORM_4F 129 
#define  UNIFORM_4FV 128 
 int /*<<< orphan*/  cgGLSetParameter1f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgGLSetParameter1fv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgGLSetParameter2f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgGLSetParameter2fv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgGLSetParameter3f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgGLSetParameter3fv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgGLSetParameter4f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgGetNamedParameter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void gl_cg_set_uniform_parameter(
      void *data,
      struct uniform_info *param,
      void *uniform_data)
{
   CGparameter location;
   cg_shader_data_t *cg        = (cg_shader_data_t*)data;

   if (!param || !param->enabled)
      return;

   if (param->lookup.enable)
   {
      char ident[64];
      CGprogram prog = 0;

      ident[0] = '\0';

      switch (param->lookup.type)
      {
         case SHADER_PROGRAM_VERTEX:
            prog = cg->prg[param->lookup.idx].vprg;
            break;
         case SHADER_PROGRAM_FRAGMENT:
         default:
            prog = cg->prg[param->lookup.idx].fprg;
            break;
      }

      if (param->lookup.add_prefix)
         snprintf(ident, sizeof(ident), "IN.%s", param->lookup.ident);
      location = cgGetNamedParameter(prog, param->lookup.add_prefix ? ident : param->lookup.ident);
   }
   else
   {
      struct uniform_cg *cg_param = (struct uniform_cg*)uniform_data;
      location = cg_param->loc;
   }

   switch (param->type)
   {
      case UNIFORM_1F:
         cgGLSetParameter1f(location, param->result.f.v0);
         break;
      case UNIFORM_2F:
         cgGLSetParameter2f(location, param->result.f.v0, param->result.f.v1);
         break;
      case UNIFORM_3F:
         cgGLSetParameter3f(location, param->result.f.v0, param->result.f.v1,
               param->result.f.v2);
         break;
      case UNIFORM_4F:
         cgGLSetParameter4f(location, param->result.f.v0, param->result.f.v1,
               param->result.f.v2, param->result.f.v3);
         break;
      case UNIFORM_1FV:
         cgGLSetParameter1fv(location, param->result.floatv);
         break;
      case UNIFORM_2FV:
         cgGLSetParameter2fv(location, param->result.floatv);
         break;
      case UNIFORM_3FV:
         cgGLSetParameter3fv(location, param->result.floatv);
         break;
      case UNIFORM_4FV:
         cgGLSetParameter3fv(location, param->result.floatv);
         break;
      case UNIFORM_1I:
         /* Unimplemented - Cg limitation */
         break;
   }
}