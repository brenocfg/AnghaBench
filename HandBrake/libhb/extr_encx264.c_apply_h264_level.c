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
struct TYPE_9__ {int i_mv_range; scalar_t__ b_transform_8x8; } ;
struct TYPE_10__ {scalar_t__ i_rc_method; double f_rf_constant; int i_vbv_max_bitrate; int i_vbv_buffer_size; } ;
struct TYPE_11__ {scalar_t__ i_cqm_preset; int i_width; int i_height; int i_fps_den; int i_fps_num; int i_keyint_max; int i_frame_reference; int i_level_idc; scalar_t__ b_interlaced; TYPE_1__ analyse; TYPE_2__ rc; int /*<<< orphan*/  i_bframe_pyramid; scalar_t__ i_bframe; scalar_t__ b_fake_interlaced; } ;
typedef  TYPE_3__ x264_param_t ;
struct TYPE_12__ {int level_idc; int dpb; int bitrate; int cpb; int mv_range; int frame_size; int mbps; scalar_t__ frame_only; } ;
typedef  TYPE_4__ x264_level_t ;
struct TYPE_13__ {int bit_depth; } ;
typedef  TYPE_5__ x264_api_t ;
typedef  int int64_t ;

/* Variables and functions */
 int MAX (void*,int) ; 
 void* MIN (int,int) ; 
 int /*<<< orphan*/  X264_B_PYRAMID_NONE ; 
 scalar_t__ X264_CQM_FLAT ; 
 scalar_t__ X264_RC_CRF ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 char** hb_h264_level_names ; 
 int* hb_h264_level_values ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int sqrt (int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 TYPE_4__* x264_levels ; 

int apply_h264_level(const x264_api_t *api, x264_param_t *param,
                     const char *h264_level, const char *h264_profile,
                     int verbose)
{
    float f_framerate;
    const x264_level_t *x264_level = NULL;
    int i, i_mb_size, i_mb_rate, i_mb_width, i_mb_height, max_mb_side, ret;

    /*
     * find the x264_level_t corresponding to the requested level
     */
    if (h264_level != NULL &&
        strcasecmp(h264_level, hb_h264_level_names[0]) != 0)
    {
        for (i = 0; hb_h264_level_values[i]; i++)
        {
            if (!strcmp(hb_h264_level_names[i], h264_level))
            {
                int val = hb_h264_level_values[i];
                for (i = 0; x264_levels[i].level_idc; i++)
                {
                    if (x264_levels[i].level_idc == val)
                    {
                        x264_level = &x264_levels[i];
                        break;
                    }
                }
                break;
            }
        }
        if (x264_level == NULL)
        {
            // error (invalid or unsupported level), abort
            hb_error("apply_h264_level: invalid level %s", h264_level);
            return -1;
        }
    }
    else if(h264_level != NULL &&
            !strcasecmp(h264_level, hb_h264_level_names[0]))
    {
        // "auto", do nothing
        return 0;
    }
    else
    {
        // error (level not a string), abort
        hb_error("apply_h264_level: no level specified");
        return -1;
    }

    /*
     * the H.264 profile determines VBV constraints
     */
    enum
    {
        // Main or Baseline (equivalent)
        HB_ENCX264_PROFILE_MAIN,
        // High (no 4:2:2 or 10-bit support, so anything lossy is equivalent)
        HB_ENCX264_PROFILE_HIGH,
        HB_ENCX264_PROFILE_HIGH10,
        // Lossless (4:2:0 8-bit for now)
        HB_ENCX264_PROFILE_HIGH444,
    } hb_encx264_profile;

    /*
     * H.264 profile
     *
     * TODO: we need to guess the profile like x264_sps_init does, otherwise
     * we'll get an error when setting a Main-incompatible VBV and
     * x264_sps_init() guesses Main profile. x264_sps_init() may eventually take
     * VBV into account when guessing profile, at which point this code can be
     * re-enabled.
     */
#if 0
    if (h264_profile != NULL && *h264_profile)
    {
        // if the user explicitly specified a profile, don't guess it
        if (!strcasecmp(h264_profile, "high444"))
        {
            hb_encx264_profile = HB_ENCX264_PROFILE_HIGH444;
        }
        else if (!strcasecmp(h264_profile, "main") ||
                 !strcasecmp(h264_profile, "baseline"))
        {
            hb_encx264_profile = HB_ENCX264_PROFILE_MAIN;
        }
        else
        {
            hb_encx264_profile = HB_ENCX264_PROFILE_HIGH;
        }
    }
    else
#endif
    {
        // guess the H.264 profile if the user didn't request one
        if (param->rc.i_rc_method == X264_RC_CRF &&
            param->rc.f_rf_constant < 1.0)
        {
            hb_encx264_profile = HB_ENCX264_PROFILE_HIGH444;
        }
        else if (param->analyse.b_transform_8x8 ||
                 param->i_cqm_preset != X264_CQM_FLAT)
        {
            if (api->bit_depth == 10)
            {
                hb_encx264_profile = HB_ENCX264_PROFILE_HIGH10;
            }
            else
            {
                hb_encx264_profile = HB_ENCX264_PROFILE_HIGH;
            }
        }
        else
        {
            hb_encx264_profile = HB_ENCX264_PROFILE_MAIN;
        }
    }

    /*
     * we need at least width and height in order to apply a level correctly
     */
    if (param->i_width <= 0 || param->i_height <= 0)
    {
        // error (invalid width or height), abort
        hb_error("apply_h264_level: invalid resolution (width: %d, height: %d)",
                 param->i_width, param->i_height);
        return -1;
    }

    /*
     * a return value of 1 means there were warnings
     */
    ret = 0;

    /*
     * some levels do not support interlaced encoding
     */
    if (x264_level->frame_only && (param->b_interlaced ||
                                   param->b_fake_interlaced))
    {
        if (verbose)
        {
            hb_log("apply_h264_level [warning]: interlaced flag not supported for level %s, disabling",
                   h264_level);
        }
        ret = 1;
        param->b_interlaced = param->b_fake_interlaced = 0;
    }

    /*
     * frame dimensions and rate (in macroblocks)
     */
    i_mb_width  = (param->i_width  + 15) / 16;
    i_mb_height = (param->i_height + 15) / 16;
    if (param->b_interlaced || param->b_fake_interlaced)
    {
        // interlaced: encoded height must divide cleanly by 32
        i_mb_height = (i_mb_height + 1) & ~1;
    }
    i_mb_size = i_mb_width * i_mb_height;
    if (param->i_fps_den <= 0 || param->i_fps_num <= 0)
    {
        i_mb_rate   = 0;
        f_framerate = 0.0;
    }
    else
    {
        i_mb_rate   = (int64_t)i_mb_size * param->i_fps_num / param->i_fps_den;
        f_framerate = (float)param->i_fps_num / param->i_fps_den;
    }

    /*
     * sanitize ref/frameref
     */
    if (param->i_keyint_max != 1)
    {
        int i_max_dec_frame_buffering =
            MAX(MIN(x264_level->dpb / i_mb_size, 16), 1);
        param->i_frame_reference =
            MIN(i_max_dec_frame_buffering, param->i_frame_reference);
        /*
         * some level and resolution combos may require as little as 1 ref;
         * bframes and b-pyramid are not compatible with this scenario
         */
        if (i_max_dec_frame_buffering < 2)
        {
            param->i_bframe = 0;
        }
        else if (i_max_dec_frame_buffering < 4)
        {
            param->i_bframe_pyramid = X264_B_PYRAMID_NONE;
        }
    }

    /*
     * set and/or sanitize the VBV (if not lossless)
     */
    if (hb_encx264_profile != HB_ENCX264_PROFILE_HIGH444)
    {
        // High profile allows for higher VBV bufsize/maxrate
        int cbp_factor;
        cbp_factor = hb_encx264_profile == HB_ENCX264_PROFILE_HIGH10 ? 12 :
                     hb_encx264_profile == HB_ENCX264_PROFILE_HIGH   ?  5 : 4;
        if (!param->rc.i_vbv_max_bitrate)
        {
            param->rc.i_vbv_max_bitrate = (x264_level->bitrate * cbp_factor) / 4;
        }
        else
        {
            param->rc.i_vbv_max_bitrate =
                MIN(param->rc.i_vbv_max_bitrate,
                    (x264_level->bitrate * cbp_factor) / 4);
        }
        if (!param->rc.i_vbv_buffer_size)
        {
            param->rc.i_vbv_buffer_size = (x264_level->cpb * cbp_factor) / 4;
        }
        else
        {
            param->rc.i_vbv_buffer_size =
                MIN(param->rc.i_vbv_buffer_size,
                    (x264_level->cpb * cbp_factor) / 4);
        }
    }

    /*
     * sanitize mvrange/mv-range
     */
    param->analyse.i_mv_range =
        MIN(param->analyse.i_mv_range,
            x264_level->mv_range >> !!param->b_interlaced);

    /*
     * TODO: check the rest of the limits
     */

    /*
     * things we can do nothing about (too late to change resolution or fps),
     * print warnings if we're not being quiet
     */
    if (x264_level->frame_size < i_mb_size)
    {
        if (verbose)
        {
            hb_log("apply_h264_level [warning]: frame size (%dx%d, %d macroblocks) too high for level %s (max. %d macroblocks)",
                   i_mb_width * 16, i_mb_height * 16, i_mb_size, h264_level,
                   x264_level->frame_size);
        }
        ret = 1;
    }
    else if (x264_level->mbps < i_mb_rate)
    {
        if (verbose)
        {
            hb_log("apply_h264_level [warning]: framerate (%.3f) too high for level %s at %dx%d (max. %.3f)",
                   f_framerate, h264_level, param->i_width, param->i_height,
                   (float)x264_level->mbps / i_mb_size);
        }
        ret = 1;
    }
    /*
     * width or height squared may not exceed 8 * frame_size (in macroblocks)
     * thus neither dimension may exceed sqrt(8 * frame_size)
     */
    max_mb_side = sqrt(x264_level->frame_size * 8);
    if (i_mb_width > max_mb_side)
    {
        if (verbose)
        {
            hb_log("apply_h264_level [warning]: frame too wide (%d) for level %s (max. %d)",
                   param->i_width, h264_level, max_mb_side * 16);
        }
        ret = 1;
    }
    if (i_mb_height > max_mb_side)
    {
        if (verbose)
        {
            hb_log("apply_h264_level [warning]: frame too tall (%d) for level %s (max. %d)",
                   param->i_height, h264_level, max_mb_side * 16);
        }
        ret = 1;
    }

    /*
     * level successfully applied, yay!
     */
    param->i_level_idc = x264_level->level_idc;
    return ret;
}