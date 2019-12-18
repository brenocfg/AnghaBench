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
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  renderer_data; TYPE_1__* renderer; } ;
typedef  TYPE_2__ font_data_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* flush ) (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* video_font_driver ; 

void font_driver_flush(unsigned width, unsigned height, void *font_data,
      video_frame_info_t *video_info)
{
   font_data_t *font = (font_data_t*)(font_data ? font_data : video_font_driver);
   if (font && font->renderer && font->renderer->flush)
      font->renderer->flush(width, height, font->renderer_data, video_info);
}