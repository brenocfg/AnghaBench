#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ i_rc_method; int i_qp_constant; int f_rf_constant; } ;
struct TYPE_8__ {TYPE_1__ rc; scalar_t__ b_fake_interlaced; scalar_t__ b_interlaced; } ;
typedef  TYPE_2__ x264_param_t ;
struct TYPE_9__ {int bit_depth; int (* param_apply_profile ) (TYPE_2__*,char const*) ;} ;
typedef  TYPE_3__ x264_api_t ;

/* Variables and functions */
 scalar_t__ X264_RC_CQP ; 
 scalar_t__ X264_RC_CRF ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 char** hb_h264_profile_names_10bit ; 
 char** hb_h264_profile_names_8bit ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 scalar_t__ strcasecmp (char const*,char const* const) ; 
 int stub1 (TYPE_2__*,char const*) ; 

__attribute__((used)) static int apply_h264_profile(const x264_api_t *api, x264_param_t *param,
                              const char *h264_profile, int verbose)
{
    const char * const * profile_names;
    if (api->bit_depth == 10)
    {
        profile_names = hb_h264_profile_names_10bit;
    }
    else
    {
        profile_names = hb_h264_profile_names_8bit;
    }
    if (h264_profile != NULL &&
        strcasecmp(h264_profile, profile_names[0]) != 0)
    {
        /*
         * baseline profile doesn't support interlacing
         */
        if ((param->b_interlaced ||
             param->b_fake_interlaced) &&
            !strcasecmp(h264_profile, "baseline"))
        {
            if (verbose)
            {
                hb_log("apply_h264_profile [warning]: baseline profile doesn't support interlacing, disabling");
            }
            param->b_interlaced = param->b_fake_interlaced = 0;
        }
        /*
         * lossless requires High 4:4:4 Predictive profile
         */
        int qp_bd_offset = 6 * (api->bit_depth - 8);
        if (strcasecmp(h264_profile, "high444") != 0 &&
            ((param->rc.i_rc_method == X264_RC_CQP && param->rc.i_qp_constant <= 0) ||
             (param->rc.i_rc_method == X264_RC_CRF && (int)(param->rc.f_rf_constant + qp_bd_offset) <= 0)))
        {
            if (verbose)
            {
                hb_log("apply_h264_profile [warning]: lossless requires high444 profile, disabling");
            }
            if (param->rc.i_rc_method == X264_RC_CQP)
            {
                param->rc.i_qp_constant = 1;
            }
            else
            {
                param->rc.f_rf_constant = 1 - qp_bd_offset;
            }
        }
        return api->param_apply_profile(param, h264_profile);
    }
    else if (!strcasecmp(h264_profile, profile_names[0]))
    {
        // "auto", do nothing
        return 0;
    }
    else
    {
        // error (profile not a string), abort
        hb_error("apply_h264_profile: no profile specified");
        return -1;
    }
}