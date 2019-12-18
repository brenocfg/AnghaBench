#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 unsigned int hqdn3d_lowpass_mul (unsigned short,unsigned char,short*) ; 

__attribute__((used)) static void hqdn3d_denoise_temporal( unsigned char * frame_src,
                                     unsigned char * frame_dst,
                                     unsigned short * frame_ant,
                                     int w, int h,
                                     short * temporal)
{
    int x, y;
    unsigned int tmp;

    temporal += 0x1000;

    for( y = 0; y < h; y++ )
    {
        for( x = 0; x < w; x++ )
        {
            frame_ant[x] = tmp = hqdn3d_lowpass_mul( frame_ant[x],
                                                     frame_src[x]<<8,
                                                     temporal );
            frame_dst[x] = (tmp+0x7F)>>8;
        }

        frame_src += w;
        frame_dst += w;
        frame_ant += w;
    }
}