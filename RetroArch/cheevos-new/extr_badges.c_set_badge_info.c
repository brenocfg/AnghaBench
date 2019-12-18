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
struct TYPE_4__ {char const** badge_id_list; int* badge_locked; } ;
typedef  TYPE_1__ badges_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_badge_menu_texture (TYPE_1__*,int) ; 

void set_badge_info (badges_ctx_t *badge_struct, int id,
      const char *badge_id, bool active)
{
   if (!badge_struct)
      return;

   badge_struct->badge_id_list[id] = badge_id;
   badge_struct->badge_locked[id]  = active;
   set_badge_menu_texture(badge_struct, id);
}