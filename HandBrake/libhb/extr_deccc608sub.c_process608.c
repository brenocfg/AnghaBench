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
struct s_write {int in_xds_mode; int /*<<< orphan*/  last_scr_sequence; TYPE_1__* data608; int /*<<< orphan*/  last_pts; scalar_t__ direct_rollup; } ;
struct TYPE_2__ {int channel; unsigned char last_c1; unsigned char last_c2; scalar_t__ mode; int /*<<< orphan*/  current_visible_scr_sequence; int /*<<< orphan*/  current_visible_start_ms; } ;

/* Variables and functions */
 scalar_t__ MODE_ROLLUP_2 ; 
 scalar_t__ MODE_ROLLUP_3 ; 
 scalar_t__ MODE_ROLLUP_4 ; 
 int cc_channel ; 
 scalar_t__ debug_608 ; 
 int /*<<< orphan*/  disCommand (unsigned char,unsigned char,struct s_write*) ; 
 int /*<<< orphan*/  handle_single (unsigned char,struct s_write*) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  write_cc_buffer (struct s_write*) ; 

__attribute__((used)) static void process608(const unsigned char *data, int length,
                       struct s_write *wb)
{
    static int textprinted = 0;
    int i;

    if (data!=NULL)
    {
        for (i=0;i<length;i=i+2)
        {
            unsigned char hi, lo;
            hi = data[i] & 0x7F; // Get rid of parity bit
            lo = data[i+1] & 0x7F; // Get rid of parity bit

            if (hi==0 && lo==0) // Just padding
                continue;
            if (hi>=0x01 && hi<=0x0E)
            {
                // XDS crap - mode. Would be nice to support it eventually
                // wb->data608->last_c1=0;
                // wb->data608->last_c2=0;
                wb->data608->channel=3; // Always channel 3
                wb->in_xds_mode=1;
            }
            if (hi==0x0F) // End of XDS block
            {
                wb->in_xds_mode=0;
                continue;
            }
            if (hi>=0x10 && hi<0x1F) // Non-character code or special/extended char
                // http://www.geocities.com/mcpoodle43/SCC_TOOLS/DOCS/CC_CODES.HTML
                // http://www.geocities.com/mcpoodle43/SCC_TOOLS/DOCS/CC_CHARS.HTML
            {
                // We were writing characters before, start a new line for
                // diagnostic output from disCommand()
                if (debug_608 && textprinted == 1 )
                {
                    hb_log("\n");
                    textprinted = 0;
                }

                wb->in_xds_mode=0; // Back to normal
                if (wb->data608->last_c1==hi && wb->data608->last_c2==lo)
                {
                    // Duplicate dual code, discard
                    continue;
                }
                wb->data608->last_c1=hi;
                wb->data608->last_c2=lo;
                disCommand (hi,lo,wb);
            }
            if (hi>=0x20) // Standard characters (always in pairs)
            {
                // Only print if the channel is active
                if (wb->data608->channel!=cc_channel)
                    continue;

                if (debug_608)
                {
                    if( textprinted == 0 )
                    {
                        hb_log("\n");
                        textprinted = 1;
                    }
                }

                handle_single(hi,wb);
                handle_single(lo,wb);
                wb->data608->last_c1=0;
                wb->data608->last_c2=0;
            }

            if ( debug_608 && !textprinted && wb->data608->channel==cc_channel )
            {   // Current FTS information after the characters are shown
                //hb_log("Current FTS: %s\n", print_mstime(wb->last_pts));
            }

            if ((wb->data608->mode == MODE_ROLLUP_2 ||
                 wb->data608->mode == MODE_ROLLUP_3 ||
                 wb->data608->mode == MODE_ROLLUP_4) &&
                wb->direct_rollup)
            {
                // If we are showing rollup on the fly (direct_rollup)
                // write a buffer now
                write_cc_buffer(wb);
                wb->data608->current_visible_start_ms = wb->last_pts;
                wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
            }
        }
    }
}