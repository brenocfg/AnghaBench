#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  uintptr_t menu_animation_ctx_tag ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_animation_kill_by_tag (uintptr_t*) ; 
 int /*<<< orphan*/  stripes_free_list_nodes (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void stripes_list_clear(file_list_t *list)
{
   menu_animation_ctx_tag tag = (uintptr_t)list;

   menu_animation_kill_by_tag(&tag);

   stripes_free_list_nodes(list, false);
}