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
struct TYPE_8__ {int frame_size; int block_align; int sample_rate; scalar_t__ codec_type; int bit_rate; } ;
struct TYPE_6__ {int num; int den; } ;
struct TYPE_7__ {TYPE_1__ time_base; TYPE_3__* codecpar; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_DATA ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int av_gcd (int,int) ; 
 int av_get_audio_frame_duration2 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void ff_parse_specific_params(AVStream *st, int *au_rate,
                              int *au_ssize, int *au_scale)
{
    AVCodecParameters *par = st->codecpar;
    int gcd;
    int audio_frame_size;

    audio_frame_size = av_get_audio_frame_duration2(par, 0);
    if (!audio_frame_size)
        audio_frame_size = par->frame_size;

    *au_ssize = par->block_align;
    if (audio_frame_size && par->sample_rate) {
        *au_scale = audio_frame_size;
        *au_rate  = par->sample_rate;
    } else if (par->codec_type == AVMEDIA_TYPE_VIDEO ||
               par->codec_type == AVMEDIA_TYPE_DATA ||
               par->codec_type == AVMEDIA_TYPE_SUBTITLE) {
        *au_scale = st->time_base.num;
        *au_rate  = st->time_base.den;
    } else {
        *au_scale = par->block_align ? par->block_align * 8 : 8;
        *au_rate  = par->bit_rate ? par->bit_rate :
                    8 * par->sample_rate;
    }
    gcd        = av_gcd(*au_scale, *au_rate);
    *au_scale /= gcd;
    *au_rate  /= gcd;
}