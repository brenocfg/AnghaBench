#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  video_smooth; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_TEXTURE_FILTER_LINEAR ; 
 int /*<<< orphan*/  D3D_TEXTURE_FILTER_POINT ; 
#define  RARCH_FILTER_LINEAR 130 
#define  RARCH_FILTER_NEAREST 129 
#define  RARCH_FILTER_UNSPEC 128 
 TYPE_2__* config_get_ptr () ; 

int32_t d3d_translate_filter(unsigned type)
{
   switch (type)
   {
      case RARCH_FILTER_UNSPEC:
         {
            settings_t *settings = config_get_ptr();
            if (!settings->bools.video_smooth)
               break;
         }
         /* fall-through */
      case RARCH_FILTER_LINEAR:
         return (int32_t)D3D_TEXTURE_FILTER_LINEAR;
      case RARCH_FILTER_NEAREST:
         break;
   }

   return (int32_t)D3D_TEXTURE_FILTER_POINT;
}