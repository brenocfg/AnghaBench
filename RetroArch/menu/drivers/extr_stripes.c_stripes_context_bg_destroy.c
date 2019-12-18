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
struct TYPE_4__ {int /*<<< orphan*/  bg; } ;
struct TYPE_5__ {TYPE_1__ textures; } ;
typedef  TYPE_2__ stripes_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_white_texture ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stripes_context_bg_destroy(stripes_handle_t *stripes)
{
   if (!stripes)
      return;
   video_driver_texture_unload(&stripes->textures.bg);
   video_driver_texture_unload(&menu_display_white_texture);
}