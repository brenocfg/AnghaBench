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
struct eia608_screen {char** characters; } ;
struct TYPE_2__ {size_t rollup_base_row; } ;

/* Variables and functions */
 int CC608_SCREEN_WIDTH ; 
 struct eia608_screen* get_current_visible_buffer (struct s_write*) ; 

__attribute__((used)) static int is_current_row_empty (struct s_write *wb)
{
    struct eia608_screen *use_buffer;
    int i;

    use_buffer = get_current_visible_buffer(wb);
    for (i=0;i<CC608_SCREEN_WIDTH;i++)
    {
        if (use_buffer->characters[wb->data608->rollup_base_row][i]!=' ')
            return 0;
    }
    return 1;
}