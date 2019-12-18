#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;
struct TYPE_4__ {char const* shader_path; } ;
typedef  TYPE_1__ d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
#define  RARCH_SHADER_CG 130 
#define  RARCH_SHADER_HLSL 129 
#define  RARCH_SHADER_NONE 128 
 int /*<<< orphan*/  RARCH_WARN (char*,...) ; 
 int /*<<< orphan*/  d3d9_process_shader (TYPE_1__*) ; 
 int /*<<< orphan*/  d3d9_restore (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char const*) ; 
 char const* strdup (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int supported_shader_type ; 
 int /*<<< orphan*/  video_shader_to_str (int) ; 

__attribute__((used)) static bool d3d9_set_shader(void *data,
      enum rarch_shader_type type, const char *path)
{
#if defined(HAVE_CG) || defined(HAVE_HLSL)
   d3d9_video_t *d3d = (d3d9_video_t*)data;

   if (!d3d)
      return false;

   if (!string_is_empty(d3d->shader_path))
      free(d3d->shader_path);
   d3d->shader_path = NULL;

   switch (type)
   {
      case RARCH_SHADER_CG:
      case RARCH_SHADER_HLSL:

         if (type != supported_shader_type)
         {
            RARCH_WARN("[D3D9]: Shader preset %s is using unsupported shader type %s, falling back to stock %s.\n",
               path, video_shader_to_str(type), video_shader_to_str(supported_shader_type));
            break;
         }
      
         if (!string_is_empty(path))
            d3d->shader_path = strdup(path);

         break;
      case RARCH_SHADER_NONE:
         break;
      default:
         RARCH_WARN("[D3D9]: Only Cg shaders are supported. Falling back to stock.\n");
   }

   if (!d3d9_process_shader(d3d) || !d3d9_restore(d3d))
   {
      RARCH_ERR("[D3D9]: Failed to set shader.\n");
      return false;
   }

   return true;
#else
   return false;
#endif
}