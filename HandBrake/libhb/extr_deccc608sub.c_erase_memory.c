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
struct s_write {int dummy; } ;
struct eia608_screen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_eia608_cc_buffer (struct eia608_screen*) ; 
 struct eia608_screen* get_current_hidden_buffer (struct s_write*) ; 
 struct eia608_screen* get_current_visible_buffer (struct s_write*) ; 

void erase_memory (struct s_write *wb, int displayed)
{
    struct eia608_screen *buf;
    if (displayed)
    {
        buf = get_current_visible_buffer(wb);
    }
    else
    {
        buf = get_current_hidden_buffer(wb);
    }
    clear_eia608_cc_buffer (buf);
}