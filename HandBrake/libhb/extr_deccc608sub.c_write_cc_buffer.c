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
struct s_write {int new_sentence; } ;
struct eia608_screen {scalar_t__ dirty; } ;

/* Variables and functions */
 struct eia608_screen* get_current_visible_buffer (struct s_write*) ; 
 int write_cc_buffer_as_ssa (struct eia608_screen*,struct s_write*) ; 

__attribute__((used)) static int write_cc_buffer(struct s_write *wb)
{
    struct eia608_screen *data;
    int wrote_something=0;

    data = get_current_visible_buffer(wb);
    if (!data->dirty)
        return 0;
    wb->new_sentence=1;
    wrote_something = write_cc_buffer_as_ssa(data, wb);
    data->dirty = 0;
    return wrote_something;
}