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
struct eia608_screen {int dummy; } ;
struct TYPE_2__ {int visible_buffer; struct eia608_screen buffer1; struct eia608_screen buffer2; } ;

/* Variables and functions */

__attribute__((used)) static struct eia608_screen *get_current_hidden_buffer(struct s_write *wb)
{
    struct eia608_screen *data;
    if (wb->data608->visible_buffer == 1)
        data = &wb->data608->buffer2;
    else
        data = &wb->data608->buffer1;
    return data;
}