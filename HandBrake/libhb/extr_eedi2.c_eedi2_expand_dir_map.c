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
 int const abs (int const) ; 
 int /*<<< orphan*/  eedi2_bit_blit (int*,int,int*,int,int,int) ; 
 int* eedi2_limlut ; 
 int /*<<< orphan*/  eedi2_sort_metrics (int*,int) ; 

void eedi2_expand_dir_map( uint8_t * mskp, int msk_pitch, uint8_t * dmskp, int dmsk_pitch,
                           uint8_t * dstp, int dst_pitch, int height, int width )
{
    int x, y, i;

    eedi2_bit_blit( dstp, dst_pitch, dmskp, dmsk_pitch, width, height );

    dmskp += dmsk_pitch;
    unsigned char *dmskpp = dmskp - dmsk_pitch;
    unsigned char *dmskpn = dmskp + dmsk_pitch;
    dstp += dst_pitch;
    mskp += msk_pitch;
    for( y = 1; y < height - 1; ++y )
    {
        for( x = 1; x < width - 1; ++x )
        {
            if( dmskp[x] != 0xFF || mskp[x] != 0xFF ) continue;
            int u = 0, order[9];
            if( dmskpp[x-1] != 0xFF ) order[u++] = dmskpp[x-1];
            if( dmskpp[x]   != 0xFF ) order[u++] = dmskpp[x];
            if( dmskpp[x+1] != 0xFF ) order[u++] = dmskpp[x+1];
            if(  dmskp[x-1] != 0xFF ) order[u++] =  dmskp[x-1];
            if(  dmskp[x+1] != 0xFF ) order[u++] =  dmskp[x+1];
            if( dmskpn[x-1] != 0xFF ) order[u++] = dmskpn[x-1];
            if( dmskpn[x]   != 0xFF ) order[u++] = dmskpn[x];
            if( dmskpn[x+1] != 0xFF ) order[u++] = dmskpn[x+1];
            if( u < 5 ) continue;
            eedi2_sort_metrics( order, u );
            const int mid = ( u & 1 ) ?
                order[u>>1] : ( order[(u-1)>>1] + order[u>>1] + 1 ) >> 1;
            int sum = 0, count = 0;
            const int lim = eedi2_limlut[abs(mid-128)>>2];
            for( i = 0; i < u; ++i )
            {
                if( abs( order[i] - mid ) <= lim )
                {
                    ++count;
                    sum += order[i];
                }
            }
            if( count < 5 ) continue;
            dstp[x] = (int)( ( (float)( sum + mid ) / (float)( count + 1 ) ) + 0.5f );
        }
        dmskpp += dmsk_pitch;
        dmskp += dmsk_pitch;
        dmskpn += dmsk_pitch;
        dstp += dst_pitch;
        mskp += msk_pitch;
    }
}