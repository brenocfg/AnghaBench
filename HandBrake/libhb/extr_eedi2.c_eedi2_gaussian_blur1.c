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
typedef  int uint8_t ;

/* Variables and functions */

void eedi2_gaussian_blur1( uint8_t * src, int src_pitch, uint8_t * tmp, int tmp_pitch, uint8_t * dst, int dst_pitch, int height, int width )
{
    uint8_t * srcp = src;
    uint8_t * dstp = tmp;
    int x, y;

    for( y = 0; y < height; ++y )
    {
        dstp[0] = ( srcp[3] * 582 + srcp[2] * 7078 + srcp[1] * 31724 +
                    srcp[0] * 26152 + 32768 ) >> 16;
        dstp[1] = ( srcp[4] * 582 + srcp[3] * 7078 +
                    ( srcp[0] + srcp[2] ) * 15862 +
                    srcp[1] * 26152 + 32768 ) >> 16;
        dstp[2] = ( srcp[5] * 582 + ( srcp[0] + srcp[4] ) * 3539 +
                    ( srcp[1] + srcp[3] ) * 15862 +
                    srcp[2]*26152 + 32768 ) >> 16;
        for( x = 3; x < width - 3; ++x )
        {
            dstp[x] = ( ( srcp[x-3] + srcp[x+3] ) * 291 +
                        ( srcp[x-2] + srcp[x+2] ) * 3539 +
                        ( srcp[x-1] + srcp[x+1] ) * 15862 +
                        srcp[x] * 26152 + 32768 ) >> 16;
        }
        dstp[x] = ( srcp[x-3] * 582 + ( srcp[x-2] + srcp[x+2] ) * 3539 +
                    ( srcp[x-1] + srcp[x+1] ) * 15862 +
                    srcp[x]   * 26152 + 32768 ) >> 16;
        ++x;
        dstp[x] = ( srcp[x-3] * 582 + srcp[x-2] * 7078 +
                    ( srcp[x-1] + srcp[x+1] ) * 15862 +
                    srcp[x] * 26152 + 32768 ) >> 16;
        ++x;
        dstp[x] = ( srcp[x-3] * 582 + srcp[x-2] * 7078 +
                    srcp[x-1] * 31724 + srcp[x] * 26152 + 32768 ) >> 16;
        srcp += src_pitch;
        dstp += tmp_pitch;
    }
    srcp = tmp;
    dstp = dst;
    unsigned char *src3p = srcp - tmp_pitch * 3;
    unsigned char *src2p = srcp - tmp_pitch * 2;
    unsigned char *srcpp = srcp - tmp_pitch;
    unsigned char *srcpn = srcp + tmp_pitch;
    unsigned char *src2n = srcp + tmp_pitch * 2;
    unsigned char *src3n = srcp + tmp_pitch * 3;
    for( x = 0; x < width; ++x )
    {
        dstp[x] = ( src3n[x] * 582 + src2n[x] * 7078 + srcpn[x] * 31724 +
                     srcp[x] * 26152 + 32768 ) >> 16;
    }
    src3p += tmp_pitch;
    src2p += tmp_pitch;
    srcpp += tmp_pitch;
    srcp += tmp_pitch;
    srcpn += tmp_pitch;
    src2n += tmp_pitch;
    src3n += tmp_pitch;
    dstp += dst_pitch;
    for( x = 0; x < width; ++x )
    {
        dstp[x] = ( src3n[x] * 582 + src2n[x] * 7078 +
                    ( srcpp[x] + srcpn[x] ) * 15862 +
                    srcp[x] * 26152 + 32768 ) >> 16;
    }
    src3p += tmp_pitch;
    src2p += tmp_pitch;
    srcpp += tmp_pitch;
    srcp += tmp_pitch;
    srcpn += tmp_pitch;
    src2n += tmp_pitch;
    src3n += tmp_pitch;
    dstp += dst_pitch;
    for( x = 0; x < width; ++x )
    {
        dstp[x] = ( src3n[x] * 582 + ( src2p[x] + src2n[x] ) * 3539 +
                    ( srcpp[x] + srcpn[x] ) * 15862 +
                    srcp[x] * 26152 + 32768 ) >> 16;
    }
    src3p += src_pitch;
    src2p += src_pitch;
    srcpp += src_pitch;
    srcp += src_pitch;
    srcpn += src_pitch;
    src2n += src_pitch;
    src3n += src_pitch;
    dstp += dst_pitch;
    for( y = 3; y < height - 3; ++y )
    {
        for( x = 0; x < width; ++x )
        {
            dstp[x] = ( ( src3p[x] + src3n[x] ) * 291 +
                        ( src2p[x] + src2n[x] ) * 3539 +
                        ( srcpp[x] + srcpn[x] ) * 15862 +
                        srcp[x] * 26152 + 32768 ) >> 16;
        }
        src3p += tmp_pitch;
        src2p += tmp_pitch;
        srcpp += tmp_pitch;
        srcp += tmp_pitch;
        srcpn += tmp_pitch;
        src2n += tmp_pitch;
        src3n += tmp_pitch;
        dstp += dst_pitch;
    }
    for( x = 0; x < width; ++x )
    {
        dstp[x] = ( src3p[x] * 582 + ( src2p[x] + src2n[x] ) *3539 +
                    ( srcpp[x] + srcpn[x] ) * 15862 +
                    srcp[x] * 26152 + 32768 ) >> 16;
    }
    src3p += tmp_pitch;
    src2p += tmp_pitch;
    srcpp += tmp_pitch;
    srcp += tmp_pitch;
    srcpn += tmp_pitch;
    src2n += tmp_pitch;
    src3n += tmp_pitch;
    dstp += dst_pitch;
    for( x = 0; x < width; ++x )
    {
        dstp[x] = ( src3p[x] * 582 + src2p[x] * 7078 +
                    ( srcpp[x] + srcpn[x] ) * 15862 +
                     srcp[x] * 26152 + 32768 ) >> 16;
    }
    src3p += tmp_pitch;
    src2p += tmp_pitch;
    srcpp += tmp_pitch;
    srcp += tmp_pitch;
    srcpn += tmp_pitch;
    src2n += tmp_pitch;
    src3n += tmp_pitch;
    dstp += dst_pitch;
    for( x = 0; x < width; ++x )
    {
        dstp[x] = ( src3p[x] * 582   + src2p[x] * 7078 +
                    srcpp[x] * 31724 +  srcp[x] * 26152 + 32768 ) >> 16;
    }
}