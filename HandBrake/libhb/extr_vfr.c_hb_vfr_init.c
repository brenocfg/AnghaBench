#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct hb_filter_private_s {int dummy; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {double num; double den; } ;
struct TYPE_8__ {int cfr; int frame_analysis_depth; int frame_analysis_duration; double frame_duration; scalar_t__ out_last_stop; TYPE_6__ vrate; scalar_t__* lost_time; scalar_t__ total_gained_time; scalar_t__ total_lost_time; scalar_t__* last_stop; scalar_t__* last_start; scalar_t__ extended_frames; scalar_t__ dropped_frames; int /*<<< orphan*/  frame_rate_list; int /*<<< orphan*/  delay_queue; int /*<<< orphan*/  job; int /*<<< orphan*/ * frame_metric; TYPE_6__ input_vrate; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_9__ {int /*<<< orphan*/  settings; TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
struct TYPE_10__ {int cfr; TYPE_6__ vrate; int /*<<< orphan*/  job; } ;
typedef  TYPE_3__ hb_filter_init_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  INT_MAX ; 
 int MAX_FRAME_ANALYSIS_DEPTH ; 
 int /*<<< orphan*/  build_gamma_lut (TYPE_1__*) ; 
 void* calloc (int,int) ; 
 int ceil (double) ; 
 int /*<<< orphan*/  hb_dict_extract_int (int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hb_dict_extract_rational (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hb_fifo_init (int,int) ; 
 int /*<<< orphan*/  hb_list_init () ; 

__attribute__((used)) static int hb_vfr_init(hb_filter_object_t *filter, hb_filter_init_t *init)
{
    filter->private_data    = calloc(1, sizeof(struct hb_filter_private_s));
    hb_filter_private_t *pv = filter->private_data;
    build_gamma_lut(pv);

    pv->cfr              = init->cfr;
    pv->input_vrate = pv->vrate = init->vrate;
    hb_dict_extract_int(&pv->cfr, filter->settings, "mode");
    hb_dict_extract_rational(&pv->vrate, filter->settings, "rate");

    // frame-drop analysis always looks at at least 2 buffers
    pv->frame_analysis_depth = 2;

    // Calculate the number of frames we need to keep in order to
    // detect "best" candidate frames to drop.
    double in_vrate  = (double)pv->input_vrate.num / pv->input_vrate.den;
    double out_vrate = (double)pv->vrate.num / pv->vrate.den;
    if (in_vrate > out_vrate)
    {
        // in_vrate / out_vrate tells us how many consecutive repeated
        // frames we can expect to see.  if the number of consecutive
        // repeated frame is < 2, we need the number of consecutive
        // non-repeated frames.  Then add 1 so that we should have
        // transitions that we can detect at both ends of a sequence.
        double factor = in_vrate / out_vrate;
        if (factor > 1.0 && factor < 2.0)
        {
            factor = 1 / (factor - 1);
        }
        pv->frame_analysis_depth = ceil(factor) + 1;

        // if we end up with an absurdly large value, limit it
        if (pv->frame_analysis_depth > MAX_FRAME_ANALYSIS_DEPTH)
        {
            pv->frame_analysis_depth = MAX_FRAME_ANALYSIS_DEPTH;
        }
    }
    pv->frame_analysis_duration = pv->frame_analysis_depth * 90000 / in_vrate;
    pv->frame_metric = calloc(pv->frame_analysis_depth, sizeof(double));
    pv->frame_metric[0] = INT_MAX;

    pv->job = init->job;

    /* Setup FIFO queue for subtitle cache */
    pv->delay_queue = hb_fifo_init( 8, 1 );
    pv->frame_rate_list = hb_list_init();


    /* VFR IVTC needs a bunch of time-keeping variables to track
      how many frames are dropped, how many are extended, what the
      last 4 start and stop times were (so they can be modified),
      how much time has been lost and gained overall, how much time
      the latest 4 frames should be extended by */
    pv->dropped_frames    = 0;
    pv->extended_frames   = 0;
    pv->last_start[0]     = 0;
    pv->last_stop[0]      = 0;
    pv->total_lost_time   = 0;
    pv->total_gained_time = 0;
    pv->lost_time[0]      = 0;
    pv->lost_time[1]      = 0;
    pv->lost_time[2]      = 0;
    pv->lost_time[3]      = 0;

    if (pv->cfr == 2)
    {
        // For PFR, we want the framerate based on the source's actual
        // framerate, unless it's higher than the specified peak framerate.
        double source_fps = (double)init->vrate.num / init->vrate.den;
        double peak_fps = (double)pv->vrate.num / pv->vrate.den;
        if (source_fps > peak_fps)
        {
            // peak framerate is lower than the source framerate.
            // so signal that the framerate will be the peak fps.
            init->vrate = pv->vrate;
        }
    }
    else
    {
        init->vrate = pv->vrate;
    }
    pv->frame_duration = (double)pv->vrate.den * 90000. / pv->vrate.num;
    pv->out_last_stop  = (int64_t)AV_NOPTS_VALUE;
    init->cfr          = pv->cfr;

    return 0;
}