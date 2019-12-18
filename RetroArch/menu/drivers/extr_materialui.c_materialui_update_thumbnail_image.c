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
typedef  int /*<<< orphan*/  materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  materialui_switch_list_view (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void materialui_update_thumbnail_image(void *userdata)
{
   materialui_handle_t *mui = (materialui_handle_t*)userdata;
   if (!mui)
      return;

   materialui_switch_list_view(mui);
}