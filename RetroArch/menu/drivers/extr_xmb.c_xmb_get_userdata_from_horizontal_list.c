#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmb_node_t ;
struct TYPE_3__ {int /*<<< orphan*/  horizontal_list; } ;
typedef  TYPE_1__ xmb_handle_t ;

/* Variables and functions */
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static xmb_node_t* xmb_get_userdata_from_horizontal_list(
      xmb_handle_t *xmb, unsigned i)
{
   return (xmb_node_t*)
      file_list_get_userdata_at_offset(xmb->horizontal_list, i);
}