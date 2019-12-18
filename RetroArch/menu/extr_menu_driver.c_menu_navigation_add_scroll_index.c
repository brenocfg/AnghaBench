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

/* Variables and functions */
 size_t SCROLL_INDEX_SIZE ; 
 size_t* scroll_index_list ; 
 size_t scroll_index_size ; 

__attribute__((used)) static void menu_navigation_add_scroll_index(size_t sel)
{
   scroll_index_list[scroll_index_size]   = sel;

   if (!((scroll_index_size + 1) >= SCROLL_INDEX_SIZE))
      scroll_index_size++;
}