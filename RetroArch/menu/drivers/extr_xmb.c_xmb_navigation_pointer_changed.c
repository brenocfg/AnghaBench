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
typedef  int /*<<< orphan*/  xmb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  xmb_selection_pointer_changed (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void xmb_navigation_pointer_changed(void *data)
{
   xmb_handle_t  *xmb  = (xmb_handle_t*)data;
   xmb_selection_pointer_changed(xmb, true);
}