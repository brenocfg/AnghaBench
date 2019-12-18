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
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;
typedef  int /*<<< orphan*/  abs_arg ;
struct TYPE_3__ {char* directory_video_shader; } ;
struct TYPE_4__ {TYPE_1__ paths; } ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 TYPE_2__* configuration_settings ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char const*,int) ; 
 int /*<<< orphan*/  path_is_absolute (char const*) ; 
 int retroarch_apply_shader (int,char const*,int) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  video_shader_is_supported (int) ; 
 int video_shader_parse_type (char const*) ; 

bool command_set_shader(const char *arg)
{
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
   enum rarch_shader_type type = video_shader_parse_type(arg);

   if (!string_is_empty(arg))
   {
      if (!video_shader_is_supported(type))
         return false;

      /* rebase on shader directory */
      if (!path_is_absolute(arg))
      {
         char abs_arg[PATH_MAX_LENGTH];
         const char *ref_path = configuration_settings->paths.directory_video_shader;
         fill_pathname_join(abs_arg,
               ref_path, arg, sizeof(abs_arg));
         arg = abs_arg;
      }
   }

   return retroarch_apply_shader(type, arg, true);
#else
   return false;
#endif
}