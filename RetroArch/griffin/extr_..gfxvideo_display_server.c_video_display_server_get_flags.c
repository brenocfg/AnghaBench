#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ gfx_ctx_flags_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_flags ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* current_display_server ; 
 int /*<<< orphan*/  current_display_server_data ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

bool video_display_server_get_flags(gfx_ctx_flags_t *flags)
{
   if (!current_display_server || !current_display_server->get_flags)
      return false;
   if (!flags)
      return false;

   flags->flags = current_display_server->get_flags(
         current_display_server_data);
   return true;
}