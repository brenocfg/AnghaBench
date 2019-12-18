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
 int /*<<< orphan*/  hqdn3d_denoise_spatial (unsigned char*,unsigned char*,unsigned short*,unsigned short*,int,int,short*,short*) ; 
 int /*<<< orphan*/  hqdn3d_denoise_temporal (unsigned char*,unsigned char*,unsigned short*,int,int,short*) ; 
 unsigned short* malloc (int) ; 

__attribute__((used)) static void hqdn3d_denoise( unsigned char * frame_src,
                            unsigned char * frame_dst,
                            unsigned short * line_ant,
                            unsigned short ** frame_ant_ptr,
                            int w,
                            int h,
                            short * spatial,
                            short * temporal )
{
    int x, y;
    unsigned short* frame_ant = (*frame_ant_ptr);

    if( !frame_ant)
    {
        unsigned char * src = frame_src;
        (*frame_ant_ptr) = frame_ant = malloc( w*h*sizeof(unsigned short) );
        for ( y = 0; y < h; y++, frame_src += w, frame_ant += w )
        {
            for( x = 0; x < w; x++ )
            {
                frame_ant[x] = frame_src[x]<<8;
            }
        }
        frame_src = src;
        frame_ant = *frame_ant_ptr;
    }

    /* If no spatial coefficients, do temporal denoise only */
    if( spatial[0] )
    {
        hqdn3d_denoise_spatial( frame_src,
                                frame_dst,
                                line_ant,
                                frame_ant,
                                w, h,
                                spatial,
                                temporal );
    }
    else
    {
        hqdn3d_denoise_temporal( frame_src,
                                 frame_dst,
                                 frame_ant,
                                 w, h,
                                 temporal);
    }
}