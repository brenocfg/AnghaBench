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
struct s_write {TYPE_1__* data608; } ;
struct TYPE_2__ {int visible_buffer; } ;

/* Variables and functions */

__attribute__((used)) static void swap_visible_buffer(struct s_write *wb)
{
    wb->data608->visible_buffer = (wb->data608->visible_buffer == 1) ? 2 : 1;
}