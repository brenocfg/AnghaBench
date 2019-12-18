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
 int /*<<< orphan*/  MUI_ANIM_DURATION_SCROLL ; 
 int /*<<< orphan*/  materialui_animate_scroll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  materialui_get_scroll (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void materialui_navigation_set(void *data, bool scroll)
{
   materialui_handle_t *mui = (materialui_handle_t*)data;
    
   if (!mui || !scroll)
      return;

   materialui_animate_scroll(
         mui,
         materialui_get_scroll(mui),
         MUI_ANIM_DURATION_SCROLL);
}