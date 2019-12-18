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
struct s_write {scalar_t__ new_channel; TYPE_1__* data608; } ;
struct TYPE_2__ {scalar_t__ channel; size_t color; size_t font; int cursor_column; } ;

/* Variables and functions */
 scalar_t__ cc_channel ; 
 unsigned char const** color_text ; 
 scalar_t__ debug_608 ; 
 unsigned char const* font_text ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 void*** pac2_attribs ; 

__attribute__((used)) static void handle_text_attr(const unsigned char c1, const unsigned char c2,
                             struct s_write *wb)
{
    // Handle channel change
    wb->data608->channel=wb->new_channel;
    if (wb->data608->channel!=cc_channel)
        return;
    if (debug_608)
        hb_log ("\r608: text_attr: %02X %02X",c1,c2);
    if ( ((c1!=0x11 && c1!=0x19) ||
        (c2<0x20 || c2>0x2f)) && debug_608)
    {
        hb_log ("\rThis is not a text attribute!\n");
    }
    else
    {
        int i = c2-0x20;
        wb->data608->color=pac2_attribs[i][0];
        wb->data608->font=pac2_attribs[i][1];
        if (debug_608)
            hb_log("  --  Color: %s,  font: %s\n",
                color_text[wb->data608->color][0],
                font_text[wb->data608->font]);
        if (wb->data608->cursor_column<31)
            wb->data608->cursor_column++;
    }
}