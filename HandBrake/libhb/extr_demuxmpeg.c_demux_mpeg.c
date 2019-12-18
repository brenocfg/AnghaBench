#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_13__ {scalar_t__ scr_delta; scalar_t__ last_scr; scalar_t__ last_pts; int /*<<< orphan*/  scr_changes; } ;
typedef  TYPE_2__ hb_psdemux_t ;
struct TYPE_12__ {scalar_t__ pcr; scalar_t__ start; scalar_t__ type; scalar_t__ stop; scalar_t__ renderOffset; scalar_t__ discontinuity; } ;
struct TYPE_14__ {struct TYPE_14__* next; TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 scalar_t__ AUDIO_BUF ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ VIDEO_BUF ; 
 int check_mpeg_scr (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  restore_chap (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  save_chap (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void demux_mpeg( hb_buffer_t *buf, hb_buffer_list_t *list_es,
                        hb_psdemux_t *state, int tolerance )
{
    while ( buf )
    {
        save_chap( state, buf );
        if ( state )
        {
            int discontinuity = 0;
            // we're keeping track of timing (i.e., not in scan)
            // check if there's a new pcr in this packet
            if ( buf->s.pcr >= 0 )
            {
                // we have a new pcr
                discontinuity = check_mpeg_scr( state, buf->s.pcr, tolerance );
                buf->s.pcr = AV_NOPTS_VALUE;
                // Some streams have consistently bad PCRs or SCRs
                // So filter out the offset
                if ( buf->s.start >= 0 )
                    state->scr_delta = buf->s.start - state->last_scr;
                else
                    state->scr_delta = 0;
            }
            if ( !discontinuity && buf->s.discontinuity )
            {
                // Buffer has been flagged as a discontinuity.  This happens
                // when a blueray changes clips.
                ++state->scr_changes;
                state->last_scr = buf->s.start;
                state->scr_delta = 0;
            }

            if ( buf->s.start >= 0 )
            {
                int64_t fdelta;
                if (buf->s.type == AUDIO_BUF || buf->s.type == VIDEO_BUF)
                {
                    if ( state->last_pts >= 0 )
                    {
                        fdelta = buf->s.start - state->last_pts;
                        if ( fdelta < -5 * 90000LL || fdelta > 5 * 90000LL )
                        {
                            // Packet too far from last. This may be a NZ TV
                            // broadcast as they like to change the PCR without
                            // sending a PCR update. Since it may be a while
                            // until they actually tell us the new PCR use the
                            // PTS as the PCR.
                            ++state->scr_changes;
                            state->last_scr = buf->s.start;
                            state->scr_delta = 0;
                        }
                    }
                    state->last_pts = buf->s.start;
                }
                if (state->last_scr != AV_NOPTS_VALUE)
                {
                    // Program streams have an SCR in every PACK header so they
                    // can't lose their clock reference. But the PCR in
                    // Transport streams is typically on <.1% of the packets.
                    // If a PCR packet gets lost and it marks a clock
                    // discontinuity then the data following it will be
                    // referenced to the wrong clock & introduce huge gaps or
                    // throw our A/V sync off. We try to protect against that
                    // here by sanity checking timestamps against the current
                    // reference clock and discarding packets where the DTS
                    // is "too far" from its clock.
                    fdelta = buf->s.start - state->last_scr - state->scr_delta;
                    if ( fdelta < -300 * 90000LL || fdelta > 300 * 90000LL )
                    {
                        // packet too far behind or ahead of its clock reference
                        buf->s.renderOffset = AV_NOPTS_VALUE;
                        buf->s.start = AV_NOPTS_VALUE;
                        buf->s.stop = AV_NOPTS_VALUE;
                    }
                    else
                    {
                        // Some streams have no PCRs.  In these cases, we
                        // will only get an "PCR" update if a large change
                        // in DTS or PTS is detected.  So we need to update
                        // our scr_delta with each valid timestamp so that
                        // fdelta does not continually grow.
                        state->scr_delta = buf->s.start - state->last_scr;
                    }
                }
            }

            if ( buf->s.type == VIDEO_BUF )
            {
                restore_chap( state, buf );
            }
        }

        hb_buffer_t *tmp = buf->next;
        buf->next = NULL;
        hb_buffer_list_append(list_es, buf);
        buf = tmp;
    }
}