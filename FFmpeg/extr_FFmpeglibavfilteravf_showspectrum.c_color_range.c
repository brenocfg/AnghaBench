#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; float nb_display_channels; int const color_mode; float rotation; float saturation; } ;
typedef  TYPE_1__ ShowSpectrumContext ;

/* Variables and functions */
#define  CHANNEL 144 
#define  CIVIDIS 143 
#define  COMBINED 142 
#define  COOL 141 
#define  FIERY 140 
#define  FIRE 139 
#define  FRUIT 138 
#define  GREEN 137 
#define  INTENSITY 136 
#define  MAGMA 135 
#define  MORELAND 134 
 float M_PI ; 
 float M_PI_2 ; 
#define  NEBULAE 133 
#define  PLASMA 132 
#define  RAINBOW 131 
#define  SEPARATE 130 
#define  TERRAIN 129 
#define  VIRIDIS 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 float cosf (float) ; 
 float sinf (float) ; 

__attribute__((used)) static void color_range(ShowSpectrumContext *s, int ch,
                        float *yf, float *uf, float *vf)
{
    switch (s->mode) {
    case COMBINED:
        // reduce range by channel count
        *yf = 256.0f / s->nb_display_channels;
        switch (s->color_mode) {
        case RAINBOW:
        case MORELAND:
        case NEBULAE:
        case FIRE:
        case FIERY:
        case FRUIT:
        case COOL:
        case GREEN:
        case VIRIDIS:
        case PLASMA:
        case CIVIDIS:
        case TERRAIN:
        case MAGMA:
        case INTENSITY:
            *uf = *yf;
            *vf = *yf;
            break;
        case CHANNEL:
            /* adjust saturation for mixed UV coloring */
            /* this factor is correct for infinite channels, an approximation otherwise */
            *uf = *yf * M_PI;
            *vf = *yf * M_PI;
            break;
        default:
            av_assert0(0);
        }
        break;
    case SEPARATE:
        // full range
        *yf = 256.0f;
        *uf = 256.0f;
        *vf = 256.0f;
        break;
    default:
        av_assert0(0);
    }

    if (s->color_mode == CHANNEL) {
        if (s->nb_display_channels > 1) {
            *uf *= 0.5f * sinf((2 * M_PI * ch) / s->nb_display_channels + M_PI * s->rotation);
            *vf *= 0.5f * cosf((2 * M_PI * ch) / s->nb_display_channels + M_PI * s->rotation);
        } else {
            *uf *= 0.5f * sinf(M_PI * s->rotation);
            *vf *= 0.5f * cosf(M_PI * s->rotation + M_PI_2);
        }
    } else {
        *uf += *uf * sinf(M_PI * s->rotation);
        *vf += *vf * cosf(M_PI * s->rotation + M_PI_2);
    }

    *uf *= s->saturation;
    *vf *= s->saturation;
}