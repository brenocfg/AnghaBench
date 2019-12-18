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
typedef  size_t uint8_t ;
struct TYPE_11__ {float* gamma_lut; scalar_t__ frames; TYPE_4__* mask; TYPE_2__** ref; scalar_t__ spatial_threshold; scalar_t__ motion_threshold; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_10__ {TYPE_3__* plane; } ;
struct TYPE_9__ {size_t* data; } ;
struct TYPE_8__ {TYPE_1__* plane; } ;
struct TYPE_7__ {int stride; int width; int height; size_t* data; } ;

/* Variables and functions */
 float fabs (float) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void detect_gamma_combed_segment( hb_filter_private_t * pv,
                                         int segment_start, int segment_stop )
{
    /* A mish-mash of various comb detection tricks
       picked up from neuron2's Decomb plugin for
       AviSynth and tritical's IsCombedT and
       IsCombedTIVTC plugins.                       */

    /* Comb scoring algorithm */
    /* Motion threshold */
    float mthresh         = (float)pv->motion_threshold / (float)255;
    /* Spatial threshold */
    float athresh         = (float)pv->spatial_threshold / (float)255;
    float athresh6        = 6 *athresh;

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
                float up_diff, down_diff;
                up_diff   = pv->gamma_lut[cur[0]] - pv->gamma_lut[cur[up_1]];
                down_diff = pv->gamma_lut[cur[0]] - pv->gamma_lut[cur[down_1]];

                if (( up_diff >  athresh && down_diff >  athresh ) ||
                    ( up_diff < -athresh && down_diff < -athresh ))
                {
                    /* The pixel above and below are different,
                       and they change in the same "direction" too.*/
                    int motion = 0;
                    if (mthresh > 0)
                    {
                        /* Make sure there's sufficient motion between frame t-1 to frame t+1. */
                        if (fabs(pv->gamma_lut[prev[0]]     - pv->gamma_lut[cur[0]]      ) > mthresh &&
                            fabs(pv->gamma_lut[cur[up_1]]   - pv->gamma_lut[next[up_1]]  ) > mthresh &&
                            fabs(pv->gamma_lut[cur[down_1]] - pv->gamma_lut[next[down_1]]) > mthresh)
                                motion++;
                        if (fabs(pv->gamma_lut[next[0]]      - pv->gamma_lut[cur[0]]     ) > mthresh &&
                            fabs(pv->gamma_lut[prev[up_1]]   - pv->gamma_lut[cur[up_1]]  ) > mthresh &&
                            fabs(pv->gamma_lut[prev[down_1]] - pv->gamma_lut[cur[down_1]]) > mthresh)
                                motion++;

                    }
                    else
                    {
                        /* User doesn't want to check for motion,
                           so move on to the spatial check.       */
                        motion = 1;
                    }

                    if (motion || pv->frames == 0)
                    {
                        float combing;
                        /* Tritical's noise-resistant combing scorer.
                           The check is done on a bob+blur convolution. */
                        combing = fabs(pv->gamma_lut[cur[up_2]] +
                                       (4 * pv->gamma_lut[cur[0]]) +
                                       pv->gamma_lut[cur[down_2]] -
                                       (3 * (pv->gamma_lut[cur[up_1]] +
                                             pv->gamma_lut[cur[down_1]])));
                        /* If the frame is sufficiently combed,
                           then mark it down on the mask as 1. */
                        if (combing > athresh6)
                        {
                            mask[0] = 1;
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