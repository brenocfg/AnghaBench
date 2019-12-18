#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  version ;
typedef  int /*<<< orphan*/  minor_str ;
typedef  int /*<<< orphan*/  major_str ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ gfx_ctx_flags_t ;
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;
typedef  enum compare_op { ____Placeholder_compare_op } compare_op ;
typedef  enum api_parse_state { ____Placeholder_api_parse_state } api_parse_state ;
struct TYPE_10__ {TYPE_2__* required_hw_api_list; } ;
typedef  TYPE_4__ core_info_t ;
struct TYPE_8__ {unsigned int size; TYPE_1__* elems; } ;
struct TYPE_7__ {char* data; } ;

/* Variables and functions */
 int COMPARE_OP_EQUAL ; 
 int COMPARE_OP_GREATER ; 
 int COMPARE_OP_GREATER_EQUAL ; 
 int COMPARE_OP_LESS ; 
 int COMPARE_OP_LESS_EQUAL ; 
 int COMPARE_OP_NOT_EQUAL ; 
 int GFX_CTX_DIRECT3D10_API ; 
 int GFX_CTX_DIRECT3D11_API ; 
 int GFX_CTX_DIRECT3D12_API ; 
 int GFX_CTX_DIRECT3D8_API ; 
 int GFX_CTX_DIRECT3D9_API ; 
 int GFX_CTX_FLAGS_GL_CORE_CONTEXT ; 
 int GFX_CTX_METAL_API ; 
 int GFX_CTX_OPENGL_API ; 
 int GFX_CTX_OPENGL_ES_API ; 
 int GFX_CTX_VULKAN_API ; 
 scalar_t__ core_info_compare_api_version (int,int,int,int,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  islower (char const) ; 
 int /*<<< orphan*/  isupper (char const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal_noncase (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int video_context_driver_get_api () ; 
 int /*<<< orphan*/  video_context_driver_get_flags (TYPE_3__*) ; 
 char* video_driver_get_gpu_api_version_string () ; 

bool core_info_hw_api_supported(core_info_t *info)
{
#ifdef RARCH_INTERNAL
   unsigned i;
   enum gfx_ctx_api sys_api;
   gfx_ctx_flags_t sys_flags       = {0};
   const char *sys_api_version_str = video_driver_get_gpu_api_version_string();
   int sys_api_version_major       = 0;
   int sys_api_version_minor       = 0;

   enum api_parse_state
   {
      STATE_API_NAME,
      STATE_API_COMPARE_OP,
      STATE_API_VERSION
   };

   if (!info || !info->required_hw_api_list || info->required_hw_api_list->size == 0)
      return true;

   sys_api = video_context_driver_get_api();
   video_context_driver_get_flags(&sys_flags);

   for (i = 0; i < info->required_hw_api_list->size; i++)
   {
      char api_str[32]           = {0};
      char version[16]           = {0};
      char major_str[16]         = {0};
      char minor_str[16]         = {0};
      const char *cur_api        = info->required_hw_api_list->elems[i].data;
      int api_pos                = 0;
      int major_str_pos          = 0;
      int minor_str_pos          = 0;
      int cur_api_len            = 0;
      int j                      = 0;
      int major                  = 0;
      int minor                  = 0;
      bool found_major           = false;
      bool found_minor           = false;
      enum compare_op op         = COMPARE_OP_GREATER_EQUAL;
      enum api_parse_state state = STATE_API_NAME;

      if (string_is_empty(cur_api))
         continue;

      cur_api_len                = (int)strlen(cur_api);

      for (j = 0; j < cur_api_len; j++)
      {
         if (cur_api[j] == ' ')
            continue;

         switch (state)
         {
            case STATE_API_NAME:
            {
               if (isupper(cur_api[j]) || islower(cur_api[j]))
                  api_str[api_pos++] = cur_api[j];
               else
               {
                  j--;
                  state = STATE_API_COMPARE_OP;
                  break;
               }

               break;
            }
            case STATE_API_COMPARE_OP:
            {
               if (j < cur_api_len - 1 && !(cur_api[j] >= '0' && cur_api[j] <= '9'))
               {
                  if (cur_api[j] == '=' && cur_api[j + 1] == '=')
                  {
                     op = COMPARE_OP_EQUAL;
                     j++;
                  }
                  else if (cur_api[j] == '=')
                     op = COMPARE_OP_EQUAL;
                  else if (cur_api[j] == '!' && cur_api[j + 1] == '=')
                  {
                     op = COMPARE_OP_NOT_EQUAL;
                     j++;
                  }
                  else if (cur_api[j] == '<' && cur_api[j + 1] == '=')
                  {
                     op = COMPARE_OP_LESS_EQUAL;
                     j++;
                  }
                  else if (cur_api[j] == '>' && cur_api[j + 1] == '=')
                  {
                     op = COMPARE_OP_GREATER_EQUAL;
                     j++;
                  }
                  else if (cur_api[j] == '<')
                     op = COMPARE_OP_LESS;
                  else if (cur_api[j] == '>')
                     op = COMPARE_OP_GREATER;
               }

               state = STATE_API_VERSION;

               break;
            }
            case STATE_API_VERSION:
            {
               if (!found_minor && cur_api[j] >= '0' && cur_api[j] <= '9' && cur_api[j] != '.')
               {
                  found_major = true;

                  if (major_str_pos < sizeof(major_str) - 1)
                     major_str[major_str_pos++] = cur_api[j];
               }
               else if (found_major && found_minor && cur_api[j] >= '0' && cur_api[j] <= '9')
               {
                  if (minor_str_pos < sizeof(minor_str) - 1)
                     minor_str[minor_str_pos++] = cur_api[j];
               }
               else if (cur_api[j] == '.')
                  found_minor = true;
               break;
            }
            default:
               break;
         }
      }

      sscanf(major_str, "%d", &major);
      sscanf(minor_str, "%d", &minor);
      snprintf(version, sizeof(version), "%d.%d", major, minor);
#if 0
      printf("Major: %d\n", major);
      printf("Minor: %d\n", minor);
      printf("API: %s\n", api_str);
      printf("Version: %s\n", version);
      fflush(stdout);
#endif

      if ((string_is_equal_noncase(api_str, "opengl") && sys_api == GFX_CTX_OPENGL_API) ||
            (string_is_equal_noncase(api_str, "openglcompat") && sys_api == GFX_CTX_OPENGL_API) ||
            (string_is_equal_noncase(api_str, "openglcompatibility") && sys_api == GFX_CTX_OPENGL_API))
      {
         /* system is running a core context while compat is requested */
         if (sys_flags.flags & (1 << GFX_CTX_FLAGS_GL_CORE_CONTEXT))   
            return false;

         sscanf(sys_api_version_str, "%d.%d", &sys_api_version_major, &sys_api_version_minor);

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "openglcore") && sys_api == GFX_CTX_OPENGL_API)
      {
         sscanf(sys_api_version_str, "%d.%d", &sys_api_version_major, &sys_api_version_minor);

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "opengles") && sys_api == GFX_CTX_OPENGL_ES_API)
      {
         sscanf(sys_api_version_str, "OpenGL ES %d.%d", &sys_api_version_major, &sys_api_version_minor);

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "direct3d8") && sys_api == GFX_CTX_DIRECT3D8_API)
      {
         sys_api_version_major = 8;
         sys_api_version_minor = 0;

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "direct3d9") && sys_api == GFX_CTX_DIRECT3D9_API)
      {
         sys_api_version_major = 9;
         sys_api_version_minor = 0;

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "direct3d10") && sys_api == GFX_CTX_DIRECT3D10_API)
      {
         sys_api_version_major = 10;
         sys_api_version_minor = 0;

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "direct3d11") && sys_api == GFX_CTX_DIRECT3D11_API)
      {
         sys_api_version_major = 11;
         sys_api_version_minor = 0;

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "direct3d12") && sys_api == GFX_CTX_DIRECT3D12_API)
      {
         sys_api_version_major = 12;
         sys_api_version_minor = 0;

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "vulkan") && sys_api == GFX_CTX_VULKAN_API)
      {
         sscanf(sys_api_version_str, "%d.%d", &sys_api_version_major, &sys_api_version_minor);

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
      else if (string_is_equal_noncase(api_str, "metal") && sys_api == GFX_CTX_METAL_API)
      {
         sscanf(sys_api_version_str, "%d.%d", &sys_api_version_major, &sys_api_version_minor);

         if (core_info_compare_api_version(sys_api_version_major, sys_api_version_minor, major, minor, op))
            return true;
      }
   }

   return false;
#else
   return true;
#endif
}