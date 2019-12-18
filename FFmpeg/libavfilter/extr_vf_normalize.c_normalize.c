#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_13__ {int** data; int height; int* linesize; int width; } ;
struct TYPE_12__ {size_t* co; int frame_num; int history_len; float independence; float* blackpt; float strength; float* whitept; int num_components; int /*<<< orphan*/  step; TYPE_1__* max; TYPE_2__* min; } ;
struct TYPE_11__ {int in; float smoothed; float out; } ;
struct TYPE_10__ {float history_sum; int* history; } ;
struct TYPE_9__ {float history_sum; int* history; } ;
typedef  TYPE_3__ NormalizeLocal ;
typedef  TYPE_4__ NormalizeContext ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 void* FFMAX (int,size_t) ; 
 float FFMAX3 (float,float,float) ; 
 void* FFMIN (int,int) ; 
 float FFMIN3 (float,float,float) ; 

__attribute__((used)) static void normalize(NormalizeContext *s, AVFrame *in, AVFrame *out)
{
    // Per-extremum, per-channel local variables.
    NormalizeLocal min[3], max[3];   // Min and max for each channel in {R,G,B}.

    float rgb_min_smoothed; // Min input range for linked normalization
    float rgb_max_smoothed; // Max input range for linked normalization
    uint8_t lut[3][256];    // Lookup table
    int x, y, c;

    // First, scan the input frame to find, for each channel, the minimum
    // (min.in) and maximum (max.in) values present in the channel.
    for (c = 0; c < 3; c++)
        min[c].in = max[c].in = in->data[0][s->co[c]];
    for (y = 0; y < in->height; y++) {
        uint8_t *inp = in->data[0] + y * in->linesize[0];
        for (x = 0; x < in->width; x++) {
            for (c = 0; c < 3; c++) {
                min[c].in = FFMIN(min[c].in, inp[s->co[c]]);
                max[c].in = FFMAX(max[c].in, inp[s->co[c]]);
            }
            inp += s->step;
        }
    }

    // Next, for each channel, push min.in and max.in into their respective
    // histories, to determine the min.smoothed and max.smoothed for this frame.
    {
        int history_idx = s->frame_num % s->history_len;
        // Assume the history is not yet full; num_history_vals is the number
        // of frames received so far including the current frame.
        int num_history_vals = s->frame_num + 1;
        if (s->frame_num >= s->history_len) {
            //The history is full; drop oldest value and cap num_history_vals.
            for (c = 0; c < 3; c++) {
                s->min[c].history_sum -= s->min[c].history[history_idx];
                s->max[c].history_sum -= s->max[c].history[history_idx];
            }
            num_history_vals = s->history_len;
        }
        // For each extremum, update history_sum and calculate smoothed value
        // as the rolling average of the history entries.
        for (c = 0; c < 3; c++) {
            s->min[c].history_sum += (s->min[c].history[history_idx] = min[c].in);
            min[c].smoothed = s->min[c].history_sum / (float)num_history_vals;
            s->max[c].history_sum += (s->max[c].history[history_idx] = max[c].in);
            max[c].smoothed = s->max[c].history_sum / (float)num_history_vals;
        }
    }

    // Determine the input range for linked normalization. This is simply the
    // minimum of the per-channel minimums, and the maximum of the per-channel
    // maximums.
    rgb_min_smoothed = FFMIN3(min[0].smoothed, min[1].smoothed, min[2].smoothed);
    rgb_max_smoothed = FFMAX3(max[0].smoothed, max[1].smoothed, max[2].smoothed);

    // Now, process each channel to determine the input and output range and
    // build the lookup tables.
    for (c = 0; c < 3; c++) {
        int in_val;
        // Adjust the input range for this channel [min.smoothed,max.smoothed]
        // by mixing in the correct proportion of the linked normalization
        // input range [rgb_min_smoothed,rgb_max_smoothed].
        min[c].smoothed = (min[c].smoothed  *         s->independence)
                        + (rgb_min_smoothed * (1.0f - s->independence));
        max[c].smoothed = (max[c].smoothed  *         s->independence)
                        + (rgb_max_smoothed * (1.0f - s->independence));

        // Calculate the output range [min.out,max.out] as a ratio of the full-
        // strength output range [blackpt,whitept] and the original input range
        // [min.in,max.in], based on the user-specified filter strength.
        min[c].out = (s->blackpt[c] *         s->strength)
                   + (min[c].in     * (1.0f - s->strength));
        max[c].out = (s->whitept[c] *         s->strength)
                   + (max[c].in     * (1.0f - s->strength));

        // Now, build a lookup table which linearly maps the adjusted input range
        // [min.smoothed,max.smoothed] to the output range [min.out,max.out].
        // Perform the linear interpolation for each x:
        //     lut[x] = (int)(float(x - min.smoothed) * scale + max.out + 0.5)
        // where scale = (max.out - min.out) / (max.smoothed - min.smoothed)
        if (min[c].smoothed == max[c].smoothed) {
            // There is no dynamic range to expand. No mapping for this channel.
            for (in_val = min[c].in; in_val <= max[c].in; in_val++)
                lut[c][in_val] = min[c].out;
        } else {
            // We must set lookup values for all values in the original input
            // range [min.in,max.in]. Since the original input range may be
            // larger than [min.smoothed,max.smoothed], some output values may
            // fall outside the [0,255] dynamic range. We need to clamp them.
            float scale = (max[c].out - min[c].out) / (max[c].smoothed - min[c].smoothed);
            for (in_val = min[c].in; in_val <= max[c].in; in_val++) {
                int out_val = (in_val - min[c].smoothed) * scale + min[c].out + 0.5f;
                out_val = FFMAX(out_val, 0);
                out_val = FFMIN(out_val, 255);
                lut[c][in_val] = out_val;
            }
        }
    }

    // Finally, process the pixels of the input frame using the lookup tables.
    for (y = 0; y < in->height; y++) {
        uint8_t *inp = in->data[0] + y * in->linesize[0];
        uint8_t *outp = out->data[0] + y * out->linesize[0];
        for (x = 0; x < in->width; x++) {
            for (c = 0; c < 3; c++)
                outp[s->co[c]] = lut[c][inp[s->co[c]]];
            if (s->num_components == 4)
                // Copy alpha as-is.
                outp[s->co[3]] = inp[s->co[3]];
            inp += s->step;
            outp += s->step;
        }
    }

    s->frame_num++;
}