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
struct TYPE_4__ {int /*<<< orphan*/  renderer_data; TYPE_1__* renderer; } ;
typedef  TYPE_2__ font_data_t ;
struct TYPE_3__ {int (* get_message_width ) (int /*<<< orphan*/ ,char const*,unsigned int,float) ;} ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 
 int stub1 (int /*<<< orphan*/ ,char const*,unsigned int,float) ; 
 void* video_font_driver ; 

int font_driver_get_message_width(void *font_data,
      const char *msg, unsigned len, float scale)
{
   font_data_t *font = (font_data_t*)(font_data ? font_data : video_font_driver);
   if (len == 0 && msg)
      len = (unsigned)strlen(msg);
   if (font && font->renderer && font->renderer->get_message_width)
      return font->renderer->get_message_width(font->renderer_data, msg, len, scale);
   return -1;
}