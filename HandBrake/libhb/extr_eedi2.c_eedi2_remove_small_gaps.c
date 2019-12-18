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
 int /*<<< orphan*/  eedi2_bit_blit (int*,int,int*,int,int,int) ; 

void eedi2_remove_small_gaps( uint8_t * mskp, int msk_pitch, uint8_t * dstp, int dst_pitch,
                              int height, int width )
{
    int x, y;

    eedi2_bit_blit( dstp, dst_pitch, mskp, msk_pitch, width, height );

    mskp += msk_pitch;
    dstp += dst_pitch;
    for( y = 1; y < height - 1; ++y )
    {
        for( x = 3; x < width - 3; ++x )
        {
            if( mskp[x] )
            {
                if( mskp[x-3] ) continue;
                if( mskp[x-2] ) continue;
                if( mskp[x-1] ) continue;
                if( mskp[x+1] ) continue;
                if( mskp[x+2] ) continue;
                if( mskp[x+3] ) continue;
                dstp[x] = 0;
            }
            else
            {
                if ( ( mskp[x+1] && ( mskp[x-1] || mskp[x-2] || mskp[x-3] ) ) ||
                     ( mskp[x+2] && ( mskp[x-1] || mskp[x-2] ) ) ||
                     ( mskp[x+3] && mskp[x-1] ) )
                    dstp[x] = 0xFF;
            }
        }
        mskp += msk_pitch;
        dstp += dst_pitch;
    }
}