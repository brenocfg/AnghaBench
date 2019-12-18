#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int height; int width; } ;
typedef  TYPE_1__ video_frame_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  GX2SetScissor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (unsigned int,int) ; 

__attribute__((used)) static void menu_display_wiiu_scissor_begin(video_frame_info_t *video_info, int x, int y,
      unsigned width, unsigned height)
{
   GX2SetScissor(MAX(x, 0), MAX(video_info->height - y - height, 0), MIN(width, video_info->width), MIN(height, video_info->height));
}