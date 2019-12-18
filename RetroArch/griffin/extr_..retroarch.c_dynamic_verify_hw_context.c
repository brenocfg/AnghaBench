#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ driver_switch_enable; } ;
struct TYPE_5__ {char* video_driver; } ;
struct TYPE_7__ {TYPE_2__ bools; TYPE_1__ arrays; } ;
typedef  TYPE_3__ settings_t ;
typedef  enum retro_hw_context_type { ____Placeholder_retro_hw_context_type } retro_hw_context_type ;

/* Variables and functions */
#define  RETRO_HW_CONTEXT_DIRECT3D 134 
#define  RETRO_HW_CONTEXT_OPENGL 133 
#define  RETRO_HW_CONTEXT_OPENGLES2 132 
#define  RETRO_HW_CONTEXT_OPENGLES3 131 
#define  RETRO_HW_CONTEXT_OPENGLES_VERSION 130 
#define  RETRO_HW_CONTEXT_OPENGL_CORE 129 
#define  RETRO_HW_CONTEXT_VULKAN 128 
 TYPE_3__* configuration_settings ; 
 int /*<<< orphan*/  string_is_equal (char const*,char*) ; 

__attribute__((used)) static bool dynamic_verify_hw_context(enum retro_hw_context_type type,
      unsigned minor, unsigned major)
{
   settings_t *settings  = configuration_settings;
   const char *video_ident = settings->arrays.video_driver;

   if (settings->bools.driver_switch_enable)
      return true;

   switch (type)
   {
      case RETRO_HW_CONTEXT_VULKAN:
         if (!string_is_equal(video_ident, "vulkan"))
            return false;
         break;
      case RETRO_HW_CONTEXT_OPENGLES2:
      case RETRO_HW_CONTEXT_OPENGLES3:
      case RETRO_HW_CONTEXT_OPENGLES_VERSION:
      case RETRO_HW_CONTEXT_OPENGL:
      case RETRO_HW_CONTEXT_OPENGL_CORE:
         if (!string_is_equal(video_ident, "gl") &&
             !string_is_equal(video_ident, "glcore"))
         {
            return false;
         }
         break;
      case RETRO_HW_CONTEXT_DIRECT3D:
         if (!(string_is_equal(video_ident, "d3d11") && major == 11))
            return false;
         break;
      default:
         break;
   }

   return true;
}