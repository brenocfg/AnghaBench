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
struct TYPE_4__ {int sidebar_entry_height; int sidebar_entry_padding_vertical; int sidebar_padding_vertical; } ;
struct TYPE_5__ {int categories_selection_ptr; int system_tab_end; TYPE_1__ dimensions; } ;
typedef  TYPE_2__ ozone_handle_t ;

/* Variables and functions */

unsigned ozone_get_selected_sidebar_y_position(ozone_handle_t *ozone)
{
   return ozone->categories_selection_ptr * ozone->dimensions.sidebar_entry_height +
         (ozone->categories_selection_ptr - 1) * ozone->dimensions.sidebar_entry_padding_vertical + ozone->dimensions.sidebar_padding_vertical +
         (ozone->categories_selection_ptr > ozone->system_tab_end ? ozone->dimensions.sidebar_entry_padding_vertical + 1 : 0);
}