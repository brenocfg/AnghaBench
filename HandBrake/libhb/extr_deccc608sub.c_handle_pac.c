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
struct s_write {int new_channel; TYPE_1__* data608; } ;
struct TYPE_2__ {int channel; size_t color; size_t font; int mode; int cursor_row; int rollup_base_row; int cursor_column; } ;

/* Variables and functions */
#define  MODE_ROLLUP_2 130 
#define  MODE_ROLLUP_3 129 
#define  MODE_ROLLUP_4 128 
 int MODE_TEXT ; 
 int cc_channel ; 
 int /*<<< orphan*/ ** color_text ; 
 scalar_t__ debug_608 ; 
 int /*<<< orphan*/ * font_text ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  move_roll_up (struct s_write*,int) ; 
 void*** pac2_attribs ; 
 int* rowdata ; 

__attribute__((used)) static void handle_pac(unsigned char c1, unsigned char c2, struct s_write *wb)
{
    // Handle channel change
    if (wb->new_channel > 2)
    {
        wb->new_channel -= 2;
        if (debug_608)
            hb_log ("\nChannel correction, now %d\n", wb->new_channel);
    }
    wb->data608->channel=wb->new_channel;
    if (wb->data608->channel!=cc_channel)
        return;

    int row=rowdata[((c1<<1)&14)|((c2>>5)&1)];

    if (debug_608)
        hb_log ("\rPAC: %02X %02X",c1,c2);

    if (c2>=0x40 && c2<=0x5f)
    {
        c2=c2-0x40;
    }
    else
    {
        if (c2>=0x60 && c2<=0x7f)
        {
            c2=c2-0x60;
        }
        else
        {
            if (debug_608)
                hb_log ("\rThis is not a PAC!!!!!\n");
            return;
        }
    }
    wb->data608->color=pac2_attribs[c2][0];
    wb->data608->font=pac2_attribs[c2][1];
    int indent=pac2_attribs[c2][2];
    if (debug_608)
        hb_log ("  --  Position: %d:%d, color: %s,  font: %s\n", row, indent,
                color_text[wb->data608->color][0],
                font_text[wb->data608->font]);

    // CC spec says to the preferred method to handle a roll-up base row
    // that causes the display to scroll off the top of the screen is to
    // adjust the base row down.
    int keep_lines;
    switch (wb->data608->mode)
    {
        case MODE_ROLLUP_2:
            keep_lines = 2;
            break;
        case MODE_ROLLUP_3:
            keep_lines = 3;
            break;
        case MODE_ROLLUP_4:
            keep_lines = 4;
            break;
        default:
            // Not rollup mode, all rows ok
            keep_lines = 0;
            break;
    }
    if (row < keep_lines)
    {
        row = keep_lines;
    }
    if (wb->data608->mode != MODE_TEXT)
    {
        // According to Robson, row info is discarded in text mode
        // but column is accepted
        //
        // CC-608 spec says current rollup display must move to the
        // new position when the cursor row changes
        move_roll_up(wb, row - 1);
        wb->data608->cursor_row = row - 1 ; // Since the array is 0 based
    }
    wb->data608->rollup_base_row = row - 1;
    wb->data608->cursor_column = indent;
}