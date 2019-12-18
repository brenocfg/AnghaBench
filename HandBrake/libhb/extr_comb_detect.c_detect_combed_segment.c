#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int spatial_metric; int motion_threshold; int spatial_threshold; scalar_t__ frames; TYPE_4__* mask; TYPE_2__** ref; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_10__ {TYPE_3__* plane; } ;
struct TYPE_9__ {int* data; } ;
struct TYPE_8__ {TYPE_1__* plane; } ;
struct TYPE_7__ {int stride; int width; int height; int* data; } ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void detect_combed_segment( hb_filter_private_t * pv,
                                   int segment_start, int segment_stop )
{
    /* A mish-mash of various comb detection tricks
       picked up from neuron2's Decomb plugin for
       AviSynth and tritical's IsCombedT and
       IsCombedTIVTC plugins.                       */


    /* Comb scoring algorithm */
    int spatial_metric  = pv->spatial_metric;
    /* Motion threshold */
    int mthresh         = pv->motion_threshold;
    /* Spatial threshold */
    int athresh         = pv->spatial_threshold;
    int athresh_squared = athresh * athresh;
    int athresh6        = 6 * athresh;

    /* One pas for Y, one pass for U, one pass for V */
    int pp;
    for (pp = 0; pp < 1; pp++)
    {
        int x, y;
        int stride  = pv->ref[0]->plane[pp].stride;
        int width   = pv->ref[0]->plane[pp].width;
        int height  = pv->ref[0]->plane[pp].height;

        /* Comb detection has to start at y = 2 and end at
           y = height - 2, because it needs to examine
           2 pixels above and 2 below the current pixel.      */
        if (segment_start < 2)
            segment_start = 2;
        if (segment_stop > height - 2)
            segment_stop = height - 2;

        for (y =  segment_start; y < segment_stop; y++)
        {
            /* These are just to make the buffer locations easier to read. */
            int up_2    = -2 * stride ;
            int up_1    = -1 * stride;
            int down_1  =      stride;
            int down_2  =  2 * stride;

            /* We need to examine a column of 5 pixels
               in the prev, cur, and next frames.      */
            uint8_t * prev = &pv->ref[0]->plane[pp].data[y * stride];
            uint8_t * cur  = &pv->ref[1]->plane[pp].data[y * stride];
            uint8_t * next = &pv->ref[2]->plane[pp].data[y * stride];
            uint8_t * mask = &pv->mask->plane[pp].data[y * stride];

            memset(mask, 0, stride);

            for (x = 0; x < width; x++)
            {
                int up_diff = cur[0] - cur[up_1];
                int down_diff = cur[0] - cur[down_1];

                if (( up_diff >  athresh && down_diff >  athresh ) ||
                    ( up_diff < -athresh && down_diff < -athresh ))
                {
                    /* The pixel above and below are different,
                       and they change in the same "direction" too.*/
                    int motion = 0;
                    if (mthresh > 0)
                    {
                        /* Make sure there's sufficient motion between frame t-1 to frame t+1. */
                        if (abs(prev[0]     - cur[0]      ) > mthresh &&
                            abs(cur[up_1]   - next[up_1]  ) > mthresh &&
                            abs(cur[down_1] - next[down_1]) > mthresh)
                                motion++;
                        if (abs(next[0]      - cur[0]     ) > mthresh &&
                            abs(prev[up_1]   - cur[up_1]  ) > mthresh &&
                            abs(prev[down_1] - cur[down_1]) > mthresh)
                                motion++;
                    }
                    else
                    {
                        /* User doesn't want to check for motion,
                           so move on to the spatial check.       */
                        motion = 1;
                    }

                    // If motion, or we can't measure motion yet...
                    if (motion || pv->frames == 0)
                    {
                           /* That means it's time for the spatial check.
                              We've got several options here.             */
                        if (spatial_metric == 0)
                        {
                            /* Simple 32detect style comb detection */
                            if ((abs(cur[0] - cur[down_2]) < 10) &&
                                (abs(cur[0] - cur[down_1]) > 15))
                            {
                                mask[0] = 1;
                            }
                        }
                        else if (spatial_metric == 1)
                        {
                            /* This, for comparison, is what IsCombed uses.
                               It's better, but still noise sensitive.      */
                               int combing = ( cur[up_1] - cur[0] ) *
                                             ( cur[down_1] - cur[0] );

                               if (combing > athresh_squared)
                               {
                                   mask[0] = 1;
                               }
                        }
                        else if (spatial_metric == 2)
                        {
                            /* Tritical's noise-resistant combing scorer.
                               The check is done on a bob+blur convolution. */
                            int combing = abs( cur[up_2]
                                             + ( 4 * cur[0] )
                                             + cur[down_2]
                                             - ( 3 * ( cur[up_1]
                                                     + cur[down_1] ) ) );

                            /* If the frame is sufficiently combed,
                               then mark it down on the mask as 1. */
                            if (combing > athresh6)
                            {
                                mask[0] = 1;
                            }
                        }
                    }
                }

                cur++;
                prev++;
                next++;
                mask++;
            }
        }
    }
}