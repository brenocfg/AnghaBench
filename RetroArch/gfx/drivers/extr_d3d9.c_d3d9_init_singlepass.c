#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
struct TYPE_6__ {int valid; double scale_y; double scale_x; int /*<<< orphan*/  type_y; int /*<<< orphan*/  type_x; } ;
struct video_shader_pass {TYPE_2__ source; TYPE_1__ fbo; } ;
struct TYPE_9__ {int passes; int /*<<< orphan*/ * pass; } ;
struct TYPE_8__ {int /*<<< orphan*/  shader_path; TYPE_4__ shader; } ;
typedef  TYPE_3__ d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_SCALE_VIEWPORT ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool d3d9_init_singlepass(d3d9_video_t *d3d)
{
   struct video_shader_pass *pass = NULL;

   if (!d3d)
      return false;

   memset(&d3d->shader, 0, sizeof(d3d->shader));
   d3d->shader.passes                    = 1;

   pass                                  = (struct video_shader_pass*)
      &d3d->shader.pass[0];

   pass->fbo.valid                       = true;
   pass->fbo.scale_y                     = 1.0;
   pass->fbo.type_y                      = RARCH_SCALE_VIEWPORT;
   pass->fbo.scale_x                     = pass->fbo.scale_y;
   pass->fbo.type_x                      = pass->fbo.type_y;

   if (!string_is_empty(d3d->shader_path))
      strlcpy(pass->source.path, d3d->shader_path,
            sizeof(pass->source.path));

   return true;
}