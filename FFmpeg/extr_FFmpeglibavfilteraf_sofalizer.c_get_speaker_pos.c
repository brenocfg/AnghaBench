#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct SOFAlizerContext {int lfe_channel; TYPE_2__* vspkrpos; scalar_t__ speakers_pos; } ;
struct TYPE_8__ {TYPE_1__** inputs; struct SOFAlizerContext* priv; } ;
struct TYPE_7__ {float azim; float elev; scalar_t__ set; } ;
struct TYPE_6__ {unsigned long long channel_layout; int channels; } ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_CH_BACK_CENTER 152 
#define  AV_CH_BACK_LEFT 151 
#define  AV_CH_BACK_RIGHT 150 
#define  AV_CH_FRONT_CENTER 149 
#define  AV_CH_FRONT_LEFT 148 
#define  AV_CH_FRONT_LEFT_OF_CENTER 147 
#define  AV_CH_FRONT_RIGHT 146 
#define  AV_CH_FRONT_RIGHT_OF_CENTER 145 
#define  AV_CH_LOW_FREQUENCY 144 
#define  AV_CH_LOW_FREQUENCY_2 143 
#define  AV_CH_SIDE_LEFT 142 
#define  AV_CH_SIDE_RIGHT 141 
#define  AV_CH_STEREO_LEFT 140 
#define  AV_CH_STEREO_RIGHT 139 
#define  AV_CH_SURROUND_DIRECT_LEFT 138 
#define  AV_CH_SURROUND_DIRECT_RIGHT 137 
#define  AV_CH_TOP_BACK_CENTER 136 
#define  AV_CH_TOP_BACK_LEFT 135 
#define  AV_CH_TOP_BACK_RIGHT 134 
#define  AV_CH_TOP_CENTER 133 
#define  AV_CH_TOP_FRONT_CENTER 132 
#define  AV_CH_TOP_FRONT_LEFT 131 
#define  AV_CH_TOP_FRONT_RIGHT 130 
#define  AV_CH_WIDE_LEFT 129 
#define  AV_CH_WIDE_RIGHT 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  parse_speaker_pos (TYPE_3__*,unsigned long long) ; 

__attribute__((used)) static int get_speaker_pos(AVFilterContext *ctx,
                           float *speaker_azim, float *speaker_elev)
{
    struct SOFAlizerContext *s = ctx->priv;
    uint64_t channels_layout = ctx->inputs[0]->channel_layout;
    float azim[16] = { 0 };
    float elev[16] = { 0 };
    int m, ch, n_conv = ctx->inputs[0]->channels; /* get no. input channels */

    if (n_conv > 16)
        return AVERROR(EINVAL);

    s->lfe_channel = -1;

    if (s->speakers_pos)
        parse_speaker_pos(ctx, channels_layout);

    /* set speaker positions according to input channel configuration: */
    for (m = 0, ch = 0; ch < n_conv && m < 64; m++) {
        uint64_t mask = channels_layout & (1ULL << m);

        switch (mask) {
        case AV_CH_FRONT_LEFT:            azim[ch] =  30;      break;
        case AV_CH_FRONT_RIGHT:           azim[ch] = 330;      break;
        case AV_CH_FRONT_CENTER:          azim[ch] =   0;      break;
        case AV_CH_LOW_FREQUENCY:
        case AV_CH_LOW_FREQUENCY_2:       s->lfe_channel = ch; break;
        case AV_CH_BACK_LEFT:             azim[ch] = 150;      break;
        case AV_CH_BACK_RIGHT:            azim[ch] = 210;      break;
        case AV_CH_BACK_CENTER:           azim[ch] = 180;      break;
        case AV_CH_SIDE_LEFT:             azim[ch] =  90;      break;
        case AV_CH_SIDE_RIGHT:            azim[ch] = 270;      break;
        case AV_CH_FRONT_LEFT_OF_CENTER:  azim[ch] =  15;      break;
        case AV_CH_FRONT_RIGHT_OF_CENTER: azim[ch] = 345;      break;
        case AV_CH_TOP_CENTER:            azim[ch] =   0;
                                          elev[ch] =  90;      break;
        case AV_CH_TOP_FRONT_LEFT:        azim[ch] =  30;
                                          elev[ch] =  45;      break;
        case AV_CH_TOP_FRONT_CENTER:      azim[ch] =   0;
                                          elev[ch] =  45;      break;
        case AV_CH_TOP_FRONT_RIGHT:       azim[ch] = 330;
                                          elev[ch] =  45;      break;
        case AV_CH_TOP_BACK_LEFT:         azim[ch] = 150;
                                          elev[ch] =  45;      break;
        case AV_CH_TOP_BACK_RIGHT:        azim[ch] = 210;
                                          elev[ch] =  45;      break;
        case AV_CH_TOP_BACK_CENTER:       azim[ch] = 180;
                                          elev[ch] =  45;      break;
        case AV_CH_WIDE_LEFT:             azim[ch] =  90;      break;
        case AV_CH_WIDE_RIGHT:            azim[ch] = 270;      break;
        case AV_CH_SURROUND_DIRECT_LEFT:  azim[ch] =  90;      break;
        case AV_CH_SURROUND_DIRECT_RIGHT: azim[ch] = 270;      break;
        case AV_CH_STEREO_LEFT:           azim[ch] =  90;      break;
        case AV_CH_STEREO_RIGHT:          azim[ch] = 270;      break;
        case 0:                                                break;
        default:
            return AVERROR(EINVAL);
        }

        if (s->vspkrpos[m].set) {
            azim[ch] = s->vspkrpos[m].azim;
            elev[ch] = s->vspkrpos[m].elev;
        }

        if (mask)
            ch++;
    }

    memcpy(speaker_azim, azim, n_conv * sizeof(float));
    memcpy(speaker_elev, elev, n_conv * sizeof(float));

    return 0;

}