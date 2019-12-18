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
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  eedi2_bit_blit (int*,int,int*,int,int,int) ; 

void eedi2_fill_gaps_2x( uint8_t *mskp, int msk_pitch, uint8_t * dmskp, int dmsk_pitch,
                         uint8_t * dstp, int dst_pitch, int field, int height, int width )
{
    int x, y, j;

    eedi2_bit_blit( dstp, dst_pitch, dmskp, dmsk_pitch, width, height );

    dmskp += dmsk_pitch * ( 2 - field );
    unsigned char *dmskpp = dmskp - dmsk_pitch * 2;
    unsigned char *dmskpn = dmskp + dmsk_pitch * 2;
    mskp += msk_pitch * ( 1 - field );
    unsigned char *mskpp = mskp - msk_pitch * 2;
    unsigned char *mskpn = mskp + msk_pitch * 2;
    unsigned char *mskpnn = mskpn + msk_pitch * 2;
    dstp += dst_pitch * ( 2 - field );
    for( y = 2 - field; y < height - 1; y += 2 )
    {
        for( x = 1; x < width - 1; ++x )
        {
            if( dmskp[x] != 0xFF ||
                ( mskp[x] != 0xFF && mskpn[x] != 0xFF ) ) continue;
            int u = x - 1, back = 500, forward = -500;
            while( u )
            {
                if( dmskp[u] != 0xFF )
                {
                    back = dmskp[u];
                    break;
                }
                if( mskp[u] != 0xFF && mskpn[u] != 0xFF ) break;
                --u;
            }
            int v = x + 1;
            while( v < width )
            {
                if( dmskp[v] != 0xFF )
                {
                    forward = dmskp[v];
                    break;
                }
                if( mskp[v] != 0xFF && mskpn[v] != 0xFF ) break;
                ++v;
            }
            int tc = 1, bc = 1;
            int mint = 500, maxt = -20;
            int minb = 500, maxb = -20;
            for( j = u; j <= v; ++j )
            {
                if( tc )
                {
                    if( y <= 2 || dmskpp[j] == 0xFF || ( mskpp[j] != 0xFF && mskp[j] != 0xFF ) )
                    {
                        tc = 0;
                        mint = maxt = 20;
                    }
                    else
                    {
                        if( dmskpp[j] < mint ) mint = dmskpp[j];
                        if( dmskpp[j] > maxt ) maxt = dmskpp[j];
                    }
                }
                if( bc )
                {
                    if( y >= height - 3 || dmskpn[j] == 0xFF || ( mskpn[j] != 0xFF && mskpnn[j] != 0xFF ) )
                    {
                        bc = 0;
                        minb = maxb = 20;
                    }
                    else
                    {
                        if( dmskpn[j] < minb ) minb = dmskpn[j];
                        if( dmskpn[j] > maxb ) maxb = dmskpn[j];
                    }
                }
            }
            if( maxt == -20 ) maxt = mint = 20;
            if( maxb == -20 ) maxb = minb = 20;
            int thresh = MAX(
                            MAX( MAX( abs( forward - 128 ), abs( back - 128 ) ) >> 2, 8 ),
                            MAX( abs( mint - maxt ), abs( minb - maxb ) ) );
            const int flim = MIN(
                                MAX( abs( forward - 128 ), abs( back - 128 ) ) >> 2,
                                6 );
            if( abs( forward - back ) <= thresh && ( v - u - 1 <= flim || tc || bc ) )
            {
                double step = (double)( forward - back ) / (double)( v - u );
                for( j = 0; j < v - u - 1; ++j )
                    dstp[u+j+1] = back + (int)( j * step + 0.5 );
            }
        }
        mskpp += msk_pitch * 2;
        mskp += msk_pitch * 2;
        mskpn += msk_pitch * 2;
        mskpnn += msk_pitch * 2;
        dmskpp += dmsk_pitch * 2;
        dmskp += dmsk_pitch * 2;
        dmskpn += dmsk_pitch * 2;
        dstp += dst_pitch * 2;
    }
}