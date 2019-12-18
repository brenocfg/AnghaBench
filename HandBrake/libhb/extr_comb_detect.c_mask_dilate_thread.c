#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  mask_dilate_taskset; TYPE_4__* mask_temp; TYPE_2__* mask_filtered; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_12__ {int segment; int* segment_start; int* segment_height; TYPE_5__* pv; } ;
typedef  TYPE_6__ decomb_thread_arg_t ;
struct TYPE_10__ {TYPE_3__* plane; } ;
struct TYPE_9__ {int* data; } ;
struct TYPE_8__ {TYPE_1__* plane; } ;
struct TYPE_7__ {int width; int height; int stride; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  hb_deep_log (int,char*,int) ; 
 int /*<<< orphan*/  taskset_thread_complete (int /*<<< orphan*/ *,int) ; 
 scalar_t__ taskset_thread_stop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskset_thread_wait4start (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mask_dilate_thread( void *thread_args_v )
{
    hb_filter_private_t * pv;
    int segment, segment_start, segment_stop;
    decomb_thread_arg_t *thread_args = thread_args_v;

    pv = thread_args->pv;
    segment = thread_args->segment;

    hb_deep_log(3, "mask dilate thread started for segment %d", segment);

    while (1)
    {
        /*
         * Wait here until there is work to do.
         */
        taskset_thread_wait4start( &pv->mask_dilate_taskset, segment );

        if (taskset_thread_stop(&pv->mask_dilate_taskset, segment))
        {
            /*
             * No more work to do, exit this thread.
             */
            break;
        }

        int xx, yy, pp;

        int count;
        int dilation_threshold = 4;

        for (pp = 0; pp < 1; pp++)
        {
            int width = pv->mask_filtered->plane[pp].width;
            int height = pv->mask_filtered->plane[pp].height;
            int stride = pv->mask_filtered->plane[pp].stride;

            int start, stop, p, c, n;
            segment_start = thread_args->segment_start[pp];
            segment_stop = segment_start + thread_args->segment_height[pp];

            if (segment_start == 0)
            {
                start = 1;
                p = 0;
                c = 1;
                n = 2;
            }
            else
            {
                start = segment_start;
                p = segment_start - 1;
                c = segment_start;
                n = segment_start + 1;
            }

            if (segment_stop == height)
            {
                stop = height -1;
            }
            else
            {
                stop = segment_stop;
            }

            uint8_t *curp = &pv->mask_filtered->plane[pp].data[p * stride + 1];
            uint8_t *cur  = &pv->mask_filtered->plane[pp].data[c * stride + 1];
            uint8_t *curn = &pv->mask_filtered->plane[pp].data[n * stride + 1];
            uint8_t *dst = &pv->mask_temp->plane[pp].data[c * stride + 1];

            for (yy = start; yy < stop; yy++)
            {
                for (xx = 1; xx < width - 1; xx++)
                {
                    if (cur[xx])
                    {
                        dst[xx] = 1;
                        continue;
                    }

                    count = curp[xx-1] + curp[xx] + curp[xx+1] +
                            cur [xx-1] +            cur [xx+1] +
                            curn[xx-1] + curn[xx] + curn[xx+1];

                    dst[xx] = count >= dilation_threshold;
                }
                curp += stride;
                cur += stride;
                curn += stride;
                dst += stride;
            }
        }

        taskset_thread_complete( &pv->mask_dilate_taskset, segment );
    }

    /*
     * Finished this segment, let everyone know.
     */
    taskset_thread_complete( &pv->mask_dilate_taskset, segment );
}