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
typedef  unsigned char uint8_t ;

/* Variables and functions */
 int MAX (int,int) ; 
 int abs (int const) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void eedi2_build_edge_mask( uint8_t * dstp, int dst_pitch, uint8_t *srcp, int src_pitch,
                            int mthresh, int lthresh, int vthresh, int height, int width )
{
    int x, y;

    mthresh = mthresh * 10;
    vthresh = vthresh * 81;

    memset( dstp, 0, ( height / 2 ) * dst_pitch );

    srcp += src_pitch;
    dstp += dst_pitch;
    unsigned char *srcpp = srcp-src_pitch;
    unsigned char *srcpn = srcp+src_pitch;
    for( y = 1; y < height - 1; ++y )
    {
        for( x = 1; x < width-1; ++x )
        {
            if( ( abs( srcpp[x]  -   srcp[x] ) < 10 &&
                  abs(  srcp[x]  -  srcpn[x] ) < 10 &&
                  abs( srcpp[x]  -  srcpn[x] ) < 10 )
              ||
                ( abs( srcpp[x-1] -  srcp[x-1] ) < 10 &&
                  abs(  srcp[x-1] - srcpn[x-1] ) < 10 &&
                  abs( srcpp[x-1] - srcpn[x-1] ) < 10 &&
                  abs( srcpp[x+1] -  srcp[x+1] ) < 10 &&
                  abs(  srcp[x+1] - srcpn[x+1] ) < 10 &&
                  abs( srcpp[x+1] - srcpn[x+1] ) < 10) )
                continue;

            const int sum = srcpp[x-1] + srcpp[x] + srcpp[x+1] +
                             srcp[x-1] +  srcp[x]+   srcp[x+1] +
                            srcpn[x-1] + srcpn[x] + srcpn[x+1];

            const int sumsq = srcpp[x-1] * srcpp[x-1] +
                              srcpp[x]   * srcpp[x]   +
                              srcpp[x+1] * srcpp[x+1] +
                               srcp[x-1] *  srcp[x-1] +
                               srcp[x]   *  srcp[x]   +
                               srcp[x+1] *  srcp[x+1] +
                              srcpn[x-1] * srcpn[x-1] +
                              srcpn[x]   * srcpn[x]   +
                              srcpn[x+1] * srcpn[x+1];

            if( 9 * sumsq-sum * sum < vthresh )
                continue;

            const int Ix = srcp[x+1] - srcp[x-1];
            const int Iy = MAX( MAX( abs( srcpp[x] - srcpn[x] ),
                                     abs( srcpp[x] -  srcp[x] ) ),
                                abs( srcp[x] - srcpn[x] ) );
            if( Ix * Ix + Iy * Iy >= mthresh )
            {
                dstp[x] = 255;
                continue;
            }

            const int Ixx =  srcp[x-1] - 2 * srcp[x] +  srcp[x+1];
            const int Iyy = srcpp[x]   - 2 * srcp[x] + srcpn[x];
            if( abs( Ixx ) + abs( Iyy ) >= lthresh )
                dstp[x] = 255;
        }
        dstp += dst_pitch;
        srcpp += src_pitch;
        srcp += src_pitch;
        srcpn += src_pitch;
    }
}