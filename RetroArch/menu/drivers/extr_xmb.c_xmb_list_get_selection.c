#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t categories_selection_ptr; } ;
typedef  TYPE_1__ xmb_handle_t ;

/* Variables and functions */

__attribute__((used)) static size_t xmb_list_get_selection(void *data)
{
   xmb_handle_t *xmb      = (xmb_handle_t*)data;

   if (!xmb)
      return 0;

   return xmb->categories_selection_ptr;
}