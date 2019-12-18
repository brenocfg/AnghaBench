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
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
#define  MODE_POPUP 132 
#define  MODE_ROLLUP_2 131 
#define  MODE_ROLLUP_3 130 
#define  MODE_ROLLUP_4 129 
#define  MODE_TEXT 128 
 struct eia608_screen* get_current_hidden_buffer (struct s_write*) ; 
 struct eia608_screen* get_current_visible_buffer (struct s_write*) ; 
 int /*<<< orphan*/  hb_error (char*) ; 

__attribute__((used)) static struct eia608_screen *get_writing_buffer(struct s_write *wb)
{
    struct eia608_screen *use_buffer=NULL;
    switch (wb->data608->mode)
    {
        case MODE_POPUP: // Write on the non-visible buffer
            use_buffer = get_current_hidden_buffer(wb);
            break;
        case MODE_ROLLUP_2: // Write directly to screen
        case MODE_ROLLUP_3:
        case MODE_ROLLUP_4:
        case MODE_TEXT:
            use_buffer = get_current_visible_buffer(wb);
            break;
        default:
            hb_error("Caption mode has an illegal value at get_writing_buffer(), this is a bug.");
    }
    return use_buffer;
}