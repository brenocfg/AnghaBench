#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* palette; int palette_set; int width; int height; } ;
typedef  TYPE_1__ hb_subtitle_t ;
struct TYPE_6__ {int extradata_size; int* extradata; int width; int height; } ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */

__attribute__((used)) static int ffmpeg_parse_vobsub_extradata_mp4( AVCodecParameters *codecpar,
                                              hb_subtitle_t *subtitle )
{
    if ( codecpar->extradata_size != 4*16 )
        return 1;

    int i, j;
    for ( i=0, j=0; i<16; i++, j+=4 )
    {
        subtitle->palette[i] =
            codecpar->extradata[j+1] << 16 |   // Y
            codecpar->extradata[j+2] << 8  |   // Cb
            codecpar->extradata[j+3] << 0;     // Cr
        subtitle->palette_set = 1;
    }
    if (codecpar->width <= 0 || codecpar->height <= 0)
    {
        subtitle->width = 720;
        subtitle->height = 480;
    }
    else
    {
        subtitle->width = codecpar->width;
        subtitle->height = codecpar->height;
    }
    return 0;
}