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
 int const abs (int) ; 
 int* eedi2_limlut ; 

void eedi2_post_process( uint8_t * nmskp, int nmsk_pitch, uint8_t * omskp, int omsk_pitch,
                         uint8_t * dstp, int src_pitch, int field, int height, int width )
{
    int x, y;

    nmskp += ( 2 - field ) * nmsk_pitch;
    omskp += ( 2 - field ) * omsk_pitch;
    dstp += ( 2 - field ) * src_pitch;
    unsigned char *srcpp = dstp - src_pitch;
    unsigned char *srcpn = dstp + src_pitch;
    for( y = 2 - field; y < height - 1; y += 2 )
    {
        for( x = 0; x < width; ++x )
        {
            const int lim = eedi2_limlut[abs(nmskp[x]-128)>>2];
            if( abs( nmskp[x] - omskp[x] ) > lim && omskp[x] != 255 && omskp[x] != 128 )
                dstp[x] = ( srcpp[x] + srcpn[x] + 1 ) >> 1;
        }
        nmskp += nmsk_pitch * 2;
        omskp += omsk_pitch * 2;
        srcpp += src_pitch * 2;
        dstp += src_pitch * 2;
        srcpn += src_pitch * 2;
    }
}