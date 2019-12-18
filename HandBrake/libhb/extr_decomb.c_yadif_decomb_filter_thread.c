#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int segment; int* segment_start; int* segment_height; TYPE_6__* pv; } ;
typedef  TYPE_4__ yadif_thread_arg_t ;
struct TYPE_15__ {int mode; int tff; int parity; TYPE_7__* dst; } ;
typedef  TYPE_5__ yadif_arguments_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int /*<<< orphan*/  yadif_taskset; TYPE_3__** ref; TYPE_5__* yadif_arguments; } ;
typedef  TYPE_6__ hb_filter_private_t ;
struct TYPE_17__ {TYPE_1__* plane; } ;
typedef  TYPE_7__ hb_buffer_t ;
struct TYPE_18__ {int* tap; int normalize; } ;
typedef  TYPE_8__ filter_param_t ;
struct TYPE_13__ {TYPE_2__* plane; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int width; int stride; int height_stride; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int MODE_DECOMB_BLEND ; 
 int MODE_DECOMB_CUBIC ; 
 int MODE_DECOMB_YADIF ; 
 int /*<<< orphan*/  blend_filter_line (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  cubic_interpolate_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskset_thread_complete (int /*<<< orphan*/ *,int) ; 
 scalar_t__ taskset_thread_stop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskset_thread_wait4start (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  yadif_filter_line (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 

__attribute__((used)) static void yadif_decomb_filter_thread( void *thread_args_v )
{
    yadif_arguments_t *yadif_work = NULL;
    hb_filter_private_t * pv;
    int segment, segment_start, segment_stop;
    yadif_thread_arg_t *thread_args = thread_args_v;
    filter_param_t filter;

    filter.tap[0] = -1;
    filter.tap[1] = 2;
    filter.tap[2] = 6;
    filter.tap[3] = 2;
    filter.tap[4] = -1;
    filter.normalize = 3;

    pv = thread_args->pv;
    segment = thread_args->segment;

    hb_deep_log(3, "yadif thread started for segment %d", segment);

    while (1)
    {
        /*
         * Wait here until there is work to do.
         */
        taskset_thread_wait4start( &pv->yadif_taskset, segment );

        if( taskset_thread_stop( &pv->yadif_taskset, segment ) )
        {
            /*
             * No more work to do, exit this thread.
             */
            break;
        }

        yadif_work = &pv->yadif_arguments[segment];

        /*
         * Process all three planes, but only this segment of it.
         */
        hb_buffer_t *dst;
        int parity, tff, mode;

        mode = pv->yadif_arguments[segment].mode;
        dst = yadif_work->dst;
        tff = yadif_work->tff;
        parity = yadif_work->parity;

        int pp;
        for (pp = 0; pp < 3; pp++)
        {
            int yy;
            int width = dst->plane[pp].width;
            int stride = dst->plane[pp].stride;
            int height = dst->plane[pp].height_stride;
            int penultimate = height - 2;

            segment_start = thread_args->segment_start[pp];
            segment_stop = segment_start + thread_args->segment_height[pp];

            // Filter parity lines
            int start = parity ? (segment_start + 1) & ~1 : segment_start | 1;
            uint8_t *dst2 = &dst->plane[pp].data[start * stride];
            uint8_t *prev = &pv->ref[0]->plane[pp].data[start * stride];
            uint8_t *cur  = &pv->ref[1]->plane[pp].data[start * stride];
            uint8_t *next = &pv->ref[2]->plane[pp].data[start * stride];

            if (mode == MODE_DECOMB_BLEND)
            {
                /* These will be useful if we ever do temporal blending. */
                for( yy = start; yy < segment_stop; yy += 2 )
                {
                    /* This line gets blend filtered, not yadif filtered. */
                    blend_filter_line(&filter, dst2, cur, width, height, stride, yy);
                    dst2 += stride * 2;
                    cur += stride * 2;
                }
            }
            else if (mode == MODE_DECOMB_CUBIC)
            {
                for( yy = start; yy < segment_stop; yy += 2 )
                {
                    /* Just apply vertical cubic interpolation */
                    cubic_interpolate_line(dst2, cur, width, height, stride, yy);
                    dst2 += stride * 2;
                    cur += stride * 2;
                }
            }
            else if (mode & MODE_DECOMB_YADIF)
            {
                for( yy = start; yy < segment_stop; yy += 2 )
                {
                    if( yy > 1 && yy < penultimate )
                    {
                        // This isn't the top or bottom,
                        // proceed as normal to yadif
                        yadif_filter_line(pv, dst2, prev, cur, next, pp,
                                          width, height, stride,
                                          parity ^ tff, yy);
                    }
                    else
                    {
                        // parity == 0 (TFF), y1 = y0
                        // parity == 1 (BFF), y0 = y1
                        // parity == 0 (TFF), yu = yp
                        // parity == 1 (BFF), yp = yu
                        int yp = (yy ^ parity) * stride;
                        memcpy(dst2, &pv->ref[1]->plane[pp].data[yp], width);
                    }
                    dst2 += stride * 2;
                    prev += stride * 2;
                    cur += stride * 2;
                    next += stride * 2;
                }
            }
            else
            {
                // No combing, copy frame
                for( yy = start; yy < segment_stop; yy += 2 )
                {
                    memcpy(dst2, cur, width);
                    dst2 += stride * 2;
                    cur += stride * 2;
                }
            }

            // Copy unfiltered lines
            start = !parity ? (segment_start + 1) & ~1 : segment_start | 1;
            dst2 = &dst->plane[pp].data[start * stride];
            prev = &pv->ref[0]->plane[pp].data[start * stride];
            cur  = &pv->ref[1]->plane[pp].data[start * stride];
            next = &pv->ref[2]->plane[pp].data[start * stride];
            for( yy = start; yy < segment_stop; yy += 2 )
            {
                memcpy(dst2, cur, width);
                dst2 += stride * 2;
                cur += stride * 2;
            }
        }
        taskset_thread_complete( &pv->yadif_taskset, segment );
    }

    /*
     * Finished this segment, let everyone know.
     */
    taskset_thread_complete( &pv->yadif_taskset, segment );
}