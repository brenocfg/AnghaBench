#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int script_initialized; int /*<<< orphan*/  ssaTrack; } ;
typedef  TYPE_3__ hb_filter_private_t ;
struct TYPE_16__ {TYPE_1__* subtitle; TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_filter_object_t ;
struct TYPE_14__ {int flags; int start; int stop; } ;
struct TYPE_17__ {TYPE_2__ s; int /*<<< orphan*/  size; scalar_t__ data; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_13__ {int /*<<< orphan*/  fifo_out; int /*<<< orphan*/  extradata_size; scalar_t__ extradata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ApplySSASubs (TYPE_3__*,TYPE_5__*) ; 
 int HB_BUF_FLAG_EOF ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_OK ; 
 int /*<<< orphan*/  ass_process_chunk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ass_process_codec_private (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_5__**) ; 
 TYPE_5__* hb_fifo_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssa_work( hb_filter_object_t * filter,
                     hb_buffer_t ** buf_in,
                     hb_buffer_t ** buf_out )
{
    hb_filter_private_t * pv = filter->private_data;
    hb_buffer_t * in = *buf_in;
    hb_buffer_t * sub;

    if (!pv->script_initialized)
    {
        // NOTE: The codec extradata is expected to be in MKV format
        // I would like to initialize this in ssa_post_init, but when we are
        // transcoding text subtitles to SSA, the extradata does not
        // get initialized until the decoder is initialized.  Since
        // decoder initialization happens after filter initialization,
        // we need to postpone this.
        ass_process_codec_private(pv->ssaTrack,
                                  (char*)filter->subtitle->extradata,
                                  filter->subtitle->extradata_size);
        pv->script_initialized = 1;
    }
    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        *buf_in = NULL;
        *buf_out = in;
        return HB_FILTER_DONE;
    }

    // Get any pending subtitles and add them to the active
    // subtitle list
    while( ( sub = hb_fifo_get( filter->subtitle->fifo_out ) ) )
    {
        if (sub->s.flags & HB_BUF_FLAG_EOF)
        {
            hb_buffer_close(&sub);
            break;
        }
        // Parse MKV-SSA packet
        // SSA subtitles always have an explicit stop time, so we
        // do not need to do special processing for stop == AV_NOPTS_VALUE
        ass_process_chunk( pv->ssaTrack, (char*)sub->data, sub->size,
                           sub->s.start / 90,
                           (sub->s.stop - sub->s.start) / 90 );
        hb_buffer_close(&sub);
    }

    ApplySSASubs( pv, in );
    *buf_in = NULL;
    *buf_out = in;

    return HB_FILTER_OK;
}