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
struct TYPE_3__ {scalar_t__ vertex; scalar_t__ fragment; } ;
struct TYPE_4__ {TYPE_1__ string; } ;
struct video_shader_pass {TYPE_2__ source; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ filestream_read_file (char const*,void**,scalar_t__*) ; 
 int /*<<< orphan*/  gl_glsl_strip_parameter_pragmas (scalar_t__,char*) ; 
 scalar_t__ strdup (scalar_t__) ; 

__attribute__((used)) static bool gl_glsl_load_source_path(struct video_shader_pass *pass,
      const char *path)
{
   int64_t len    = 0;
   int64_t nitems = pass ? filestream_read_file(path,
         (void**)&pass->source.string.vertex, &len) : 0;

   if (nitems <= 0 || len <= 0)
      return false;

   gl_glsl_strip_parameter_pragmas(pass->source.string.vertex, "#pragma parameter");
   pass->source.string.fragment = strdup(pass->source.string.vertex);
   return pass->source.string.fragment && pass->source.string.vertex;
}