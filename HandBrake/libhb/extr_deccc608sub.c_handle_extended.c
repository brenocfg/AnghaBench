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
struct TYPE_2__ {int channel; scalar_t__ cursor_column; } ;

/* Variables and functions */
 int cc_channel ; 
 scalar_t__ debug_608 ; 
 int /*<<< orphan*/  hb_log (char*,unsigned char,...) ; 
 int /*<<< orphan*/  write_char (unsigned char,struct s_write*) ; 

__attribute__((used)) static unsigned char handle_extended(unsigned char hi, unsigned char lo,
                                     struct s_write *wb)
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
        return 0;

    // For lo values between 0x20-0x3f
    unsigned char c=0;

    if (debug_608)
        hb_log ("\rExtended: %02X %02X\n",hi,lo);
    if (lo>=0x20 && lo<=0x3f && (hi==0x12 || hi==0x13))
    {
        switch (hi)
        {
            case 0x12:
                c=lo+0x70; // So if c>=0x90 && c<=0xaf it comes from here
                break;
            case 0x13:
                c=lo+0x90; // So if c>=0xb0 && c<=0xcf it comes from here
                break;
        }
        // This column change is because extended characters replace
        // the previous character (which is sent for basic decoders
        // to show something similar to the real char)
        if (wb->data608->cursor_column>0)
            wb->data608->cursor_column--;

        write_char (c,wb);
    }
    return 1;
}