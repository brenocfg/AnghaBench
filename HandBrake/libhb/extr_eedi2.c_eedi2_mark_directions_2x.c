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
 int* eedi2_limlut ; 
 int /*<<< orphan*/  eedi2_sort_metrics (int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

void eedi2_mark_directions_2x( uint8_t * mskp, int msk_pitch, uint8_t * dmskp, int dmsk_pitch,
                               uint8_t * dstp, int dst_pitch, int tff, int height, int width )
{
    int x, y, i;
    memset( dstp, 255, dst_pitch * height );
    dstp  += dst_pitch  * ( 2 - tff );
    dmskp += dmsk_pitch * ( 1 - tff );
    mskp  += msk_pitch  * ( 1 - tff );
    unsigned char *dmskpn = dmskp + dmsk_pitch * 2;
    unsigned char *mskpn = mskp + msk_pitch * 2;
    for( y = 2 - tff; y < height - 1; y += 2 )
    {
        for( x = 1; x < width - 1; ++x )
        {
            if( mskp[x] != 0xFF && mskpn[x] != 0xFF ) continue;
            int v = 0, order[6];
            if(  dmskp[x-1] != 0xFF ) order[v++] = dmskp[x-1];
            if(  dmskp[x]   != 0xFF ) order[v++] = dmskp[x];
            if(  dmskp[x+1] != 0xFF ) order[v++] = dmskp[x+1];
            if( dmskpn[x-1] != 0xFF ) order[v++] = dmskpn[x-1];
            if( dmskpn[x]   != 0xFF ) order[v++] = dmskpn[x];
            if( dmskpn[x+1] != 0xFF ) order[v++] = dmskpn[x+1];
            if( v < 3 ) continue;
            else
            {
                eedi2_sort_metrics( order, v );
                const int mid = ( v & 1 ) ? order[v>>1] : ( order[(v-1)>>1] + order[v>>1]+1) >> 1;
                const int lim = eedi2_limlut[abs(mid-128)>>2];
                int u = 0;
                if( abs( dmskp[x-1] - dmskpn[x-1] ) <= lim ||
                    dmskp[x-1] == 0xFF || dmskpn[x-1] == 0xFF )
                        ++u;
                if( abs( dmskp[x]   - dmskpn[x] )   <= lim ||
                    dmskp[x]   == 0xFF || dmskpn[x]   == 0xFF )
                        ++u;
                if( abs( dmskp[x+1] - dmskpn[x-1] ) <= lim ||
                    dmskp[x+1] == 0xFF || dmskpn[x+1] == 0xFF)
                        ++u;
                if( u < 2 ) continue;
                int count = 0, sum = 0;
                for( i = 0; i < v; ++i )
                {
                    if( abs( order[i] - mid ) <= lim )
                    {
                        ++count;
                        sum += order[i];
                    }
                }
                if( count < v - 2 || count < 2 ) continue;
                dstp[x] = (int)( ( (float)( sum + mid ) / (float)( count + 1 ) ) + 0.5f );
            }
        }
        mskp += msk_pitch * 2;
        mskpn += msk_pitch * 2;
        dstp += dst_pitch * 2;
        dmskp += dmsk_pitch * 2;
        dmskpn += dmsk_pitch * 2;
    }
}