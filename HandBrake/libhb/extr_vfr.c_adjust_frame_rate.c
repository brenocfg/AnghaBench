#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  double int64_t ;
struct TYPE_19__ {int cfr; double out_last_stop; int frame_analysis_depth; double frame_duration; int /*<<< orphan*/  count_frames; int /*<<< orphan*/  dups; scalar_t__* frame_metric; int /*<<< orphan*/  frame_rate_list; int /*<<< orphan*/  drops; int /*<<< orphan*/  gamma_lut; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_18__ {double stop; double start; double pcr; scalar_t__ new_chap; } ;
struct TYPE_20__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  delete_metric (scalar_t__*,int,int) ; 
 int find_drop_frame (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_3__**) ; 
 TYPE_3__* hb_buffer_dup (TYPE_3__*) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_3__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  hb_log (char*,double,double,...) ; 
 scalar_t__ motion_metric (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static hb_buffer_t * adjust_frame_rate( hb_filter_private_t * pv,
                                        hb_buffer_t * in )
{

    if (pv->cfr == 0)
    {
        ++pv->count_frames;
        pv->out_last_stop = in->s.stop;
        return in;
    }

    int count;

    // in == NULL signals we are flushing the frame_rate_list
    if (in != NULL)
    {
        if (pv->out_last_stop == (int64_t)AV_NOPTS_VALUE)
        {
            pv->out_last_stop = in->s.start;
        }

#if defined(HB_DEBUG_CFR_DROPS)
        in->s.pcr = pv->sequence++;
#endif
        hb_list_add(pv->frame_rate_list, in);
        count = hb_list_count(pv->frame_rate_list);
        if (count < 2)
        {
            return NULL;
        }

        hb_buffer_t * penultimate, * ultimate;
        penultimate = hb_list_item(pv->frame_rate_list, count - 2);
        ultimate    = hb_list_item(pv->frame_rate_list, count - 1);

        pv->frame_metric[count - 1] = motion_metric(pv->gamma_lut,
                                                    penultimate, ultimate);

        if (count < pv->frame_analysis_depth)
        {
            return NULL;
        }
    }
    else
    {
        count = hb_list_count(pv->frame_rate_list);
    }

    hb_buffer_list_t   list;
    hb_buffer_t      * out;
    double             cfr_stop;
    int                drop_frame;

    hb_buffer_list_clear(&list);

    drop_frame = find_drop_frame(pv, count);
    if (drop_frame >= 0)
    {

        // We may have to drop multiple frames.  Pick frames to drop
        // that appear to have minimum motion.
        //
        // The main use case we are trying to cover here is
        // "progressive telecine" where there is a repeating pattern
        // of a new frame followed by some number of repeated frames.
        // We want to keep the "new frames" and drop the repeates.
        out = hb_list_item(pv->frame_rate_list, drop_frame);

#if defined(HB_DEBUG_CFR_DROPS)
        hb_log("CFR Drop: %ld metric %d", out->s.pcr, (int)pv->frame_metric[drop_frame]);
        int jj;
        for (jj = 0; jj < count; jj++)
        {
            if (jj == drop_frame)
            {
                fprintf(stderr, "(%4d) ", (int)pv->frame_metric[jj]);
            }
            else
            {
                fprintf(stderr, "%6d ", (int)pv->frame_metric[jj]);
            }
        }
        fprintf(stderr, "\n");
#endif

        hb_list_rem(pv->frame_rate_list, out);
        hb_buffer_close(&out);
        delete_metric(pv->frame_metric, drop_frame, count);
        ++pv->drops;
        return NULL;
    }

    out = hb_list_item(pv->frame_rate_list, 0);

#if defined(HB_DEBUG_CFR_DROPS)
    static int64_t lastpass = 0;
    hb_log("CFR Pass: %ld ~ %ld metric %d", out->s.pcr, out->s.pcr - lastpass, (int)pv->frame_metric[0]);
    lastpass = out->s.pcr;
#endif

    hb_list_rem(pv->frame_rate_list, out);
    hb_buffer_list_append(&list, out);
    delete_metric(pv->frame_metric, 0, count);

    // this frame has to start where the last one stopped.
    out->s.start = pv->out_last_stop;
    cfr_stop = pv->out_last_stop + pv->frame_duration;

    // at this point we know that this frame doesn't push the average
    // rate over the limit so we just pass it on for PFR. For CFR we're
    // going to return it (with its start & stop times modified) and
    // we may have to dup it.
    ++pv->count_frames;
    if (pv->cfr > 1)
    {
        // PFR - we're going to keep the frame but may need to
        // adjust it's stop time to meet the average rate constraint.
        if (out->s.stop < cfr_stop)
        {
            out->s.stop = pv->out_last_stop = cfr_stop;
        }
        else
        {
            pv->out_last_stop = out->s.stop;
        }
    }
    else
    {
        // we're doing CFR so we have to either trim some time from a
        // buffer that ends too far in the future or, if the buffer is
        // two or more frame times long, split it into multiple pieces,
        // each of which is a frame time long.
        double excess = (double)out->s.stop - cfr_stop;
        out->s.stop = pv->out_last_stop = cfr_stop;
        for (; excess >= pv->frame_duration; excess -= pv->frame_duration)
        {
            /* next frame too far ahead - dup current frame */
            hb_buffer_t *dup = hb_buffer_dup( out );
            dup->s.new_chap = 0;
            dup->s.start = cfr_stop;
            cfr_stop += pv->frame_duration;
            dup->s.stop = pv->out_last_stop = cfr_stop;
            hb_buffer_list_append(&list, dup);
            ++pv->dups;
            ++pv->count_frames;
        }
    }

    return hb_buffer_list_clear(&list);
}