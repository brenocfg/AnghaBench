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
struct eia608_screen {unsigned char** characters; int* row_used; int dirty; scalar_t__ empty; int /*<<< orphan*/ ** fonts; int /*<<< orphan*/ ** colors; } ;
struct TYPE_2__ {scalar_t__ mode; size_t cursor_row; size_t cursor_column; int /*<<< orphan*/  font; int /*<<< orphan*/  color; } ;

/* Variables and functions */
 scalar_t__ MODE_TEXT ; 
 struct eia608_screen* get_writing_buffer (struct s_write*) ; 

__attribute__((used)) static void write_char(const unsigned char c, struct s_write *wb)
{
    if (wb->data608->mode != MODE_TEXT)
    {
        struct eia608_screen * use_buffer = get_writing_buffer(wb);
        if (use_buffer != NULL)
        {
            /* hb_log ("\rWriting char [%c] at %s:%d:%d\n",c,
            use_buffer == &wb->data608->buffer1?"B1":"B2",
            wb->data608->cursor_row,wb->data608->cursor_column); */
            use_buffer->characters[wb->data608->cursor_row][wb->data608->cursor_column] = c;
            use_buffer->colors[wb->data608->cursor_row][wb->data608->cursor_column] = wb->data608->color;
            use_buffer->fonts[wb->data608->cursor_row][wb->data608->cursor_column] = wb->data608->font;
            use_buffer->row_used[wb->data608->cursor_row] = 1;
            use_buffer->empty = 0;
            if (wb->data608->cursor_column < 31)
                wb->data608->cursor_column++;
            use_buffer->dirty = 1;
        }
    }

}