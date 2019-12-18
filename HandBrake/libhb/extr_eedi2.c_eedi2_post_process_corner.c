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

void eedi2_post_process_corner( int *x2, int *y2, int *xy, const int pitch, uint8_t * mskp, int msk_pitch, uint8_t * dstp, int dst_pitch, int height, int width, int field )
{
    mskp += ( 8 - field ) * msk_pitch;
    dstp += ( 8 - field ) * dst_pitch;
    unsigned char * dstpp = dstp - dst_pitch;
    unsigned char * dstpn = dstp + dst_pitch;
    x2 += pitch * 3;
    y2 += pitch * 3;
    xy += pitch * 3;
    int *x2n = x2 + pitch;
    int *y2n = y2 + pitch;
    int *xyn = xy + pitch;
    int x, y;

    for( y = 8 - field; y < height - 7; y += 2 )
    {
        for( x = 4; x < width - 4; ++x )
        {
            if( mskp[x] == 255 || mskp[x] == 128 ) continue;
            const int c1 = (int)( x2[x]  *  y2[x] -  xy[x] * xy[x] - 0.09 *
                                  ( x2[x]  + y2[x] )  * ( x2[x]  + y2[x] ) );
            const int c2 = (int)( x2n[x] * y2n[x] - xyn[x]* xyn[x] - 0.09 *
                                  ( x2n[x] + y2n[x] ) * ( x2n[x] + y2n[x] ) );
            if (c1 > 775 || c2 > 775)
                dstp[x] = ( dstpp[x] + dstpn[x] + 1 ) >> 1;
        }
        mskp += msk_pitch * 2;
        dstpp += dst_pitch * 2;
        dstp += dst_pitch * 2;
        dstpn += dst_pitch * 2;
        x2 += pitch;
        x2n += pitch;
        y2 += pitch;
        y2n += pitch;
        xy += pitch;
        xyn += pitch;
    }
}