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
struct shader_program_cg {int /*<<< orphan*/  vprg; int /*<<< orphan*/  fprg; } ;
struct cg_fbo_params {void* coord; void* tex_size_f; void* tex_size_v; void* vid_size_f; void* vid_size_v; void* tex; } ;
typedef  int /*<<< orphan*/  attr_buf ;

/* Variables and functions */
 void* cgGetNamedParameter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void gl_cg_set_pass_attrib(
      struct shader_program_cg *program,
      struct cg_fbo_params *fbo,
      const char *attr)
{
   char attr_buf[64];

   attr_buf[0] = '\0';

   snprintf(attr_buf, sizeof(attr_buf), "%s.texture", attr);
   if (!fbo->tex)
      fbo->tex = cgGetNamedParameter(program->fprg, attr_buf);

   snprintf(attr_buf, sizeof(attr_buf), "%s.video_size", attr);
   if (!fbo->vid_size_v)
      fbo->vid_size_v = cgGetNamedParameter(program->vprg, attr_buf);
   if (!fbo->vid_size_f)
      fbo->vid_size_f = cgGetNamedParameter(program->fprg, attr_buf);

   snprintf(attr_buf, sizeof(attr_buf), "%s.texture_size", attr);
   if (!fbo->tex_size_v)
      fbo->tex_size_v = cgGetNamedParameter(program->vprg, attr_buf);
   if (!fbo->tex_size_f)
      fbo->tex_size_f = cgGetNamedParameter(program->fprg, attr_buf);

   snprintf(attr_buf, sizeof(attr_buf), "%s.tex_coord", attr);
   if (!fbo->coord)
      fbo->coord = cgGetNamedParameter(program->vprg, attr_buf);
}