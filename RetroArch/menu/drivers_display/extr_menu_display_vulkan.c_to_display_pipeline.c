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
typedef  enum menu_display_prim_type { ____Placeholder_menu_display_prim_type } menu_display_prim_type ;

/* Variables and functions */
 int MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 

__attribute__((used)) static unsigned to_display_pipeline(
      enum menu_display_prim_type type, bool blend)
{
   return ((type == MENU_DISPLAY_PRIM_TRIANGLESTRIP) << 1) | (blend << 0);
}