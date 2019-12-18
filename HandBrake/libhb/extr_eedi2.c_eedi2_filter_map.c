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
 int MAX (int,int const) ; 
 int MIN (int,int const) ; 
 int const abs (int const) ; 
 int /*<<< orphan*/  eedi2_bit_blit (int*,int,int*,int,int,int) ; 

void eedi2_filter_map( uint8_t * mskp, int msk_pitch, uint8_t * dmskp, int dmsk_pitch,
                       uint8_t * dstp, int dst_pitch, int height, int width )
{
    int x, y, j;

    eedi2_bit_blit( dstp, dst_pitch, dmskp, dmsk_pitch, width, height );

    mskp += msk_pitch;
    dmskp += dmsk_pitch;
    dstp += dst_pitch;
    unsigned char *dmskpp = dmskp - dmsk_pitch;
    unsigned char *dmskpn = dmskp + dmsk_pitch;

    for( y = 1; y < height - 1; ++y )
    {
        for( x = 1; x < width - 1; ++x )
        {
            if( dmskp[x] == 0xFF || mskp[x] != 0xFF )
                continue;
            const int dir = ( dmskp[x] - 128 ) >> 2;
            const int lim = MAX( abs( dir ) * 2, 12 );
            int ict = 0, icb = 0;
            if( dir < 0 )
            {
                const int dirt = MAX( -x, dir );
                for( j = dirt; j <= 0; ++j )
                {
                    if( ( abs( dmskpp[x+j] - dmskp[x] ) > lim && dmskpp[x+j] != 0xFF ) ||
                        ( dmskp[x+j] == 0xFF && dmskpp[x+j] == 0xFF ) ||
                        ( abs(  dmskp[x+j] - dmskp[x] ) > lim &&  dmskp[x+j] != 0xFF ) )
                    {
                        ict = 1;
                        break;
                    }
                }
            }
            else
            {
                const int dirt = MIN( width - x - 1, dir );
                for( j = 0; j <= dirt; ++j )
                {
                    if( ( abs( dmskpp[x+j] - dmskp[x] ) > lim && dmskpp[x+j] != 0xFF ) ||
                        ( dmskp[x+j] == 0xFF && dmskpp[x+j] == 0xFF ) ||
                        ( abs(  dmskp[x+j] - dmskp[x] ) > lim &&  dmskp[x+j] != 0xFF ) )
                    {
                        ict = 1;
                        break;
                    }
                }
            }
            if( ict )
            {
                if( dir < 0 )
                {
                    const int dirt = MIN( width - x - 1, abs( dir ) );
                    for( j = 0; j <= dirt; ++j )
                    {
                        if( ( abs( dmskpn[x+j] - dmskp[x] ) > lim && dmskpn[x+j] != 0xFF ) ||
                            ( dmskpn[x+j] == 0xFF && dmskp[x+j] == 0xFF ) ||
                            ( abs(  dmskp[x+j] - dmskp[x] ) > lim &&  dmskp[x+j] != 0xFF ) )
                        {
                            icb = 1;
                            break;
                        }
                    }
                }
                else
                {
                    const int dirt = MAX( -x, -dir );
                    for( j = dirt; j <= 0; ++j )
                    {
                        if( ( abs( dmskpn[x+j] - dmskp[x] ) > lim && dmskpn[x+j] != 0xFF ) ||
                            ( dmskpn[x+j] == 0xFF && dmskp[x+j] == 0xFF ) ||
                            ( abs(  dmskp[x+j] - dmskp[x] ) > lim &&  dmskp[x+j] != 0xFF ) )
                        {
                            icb = 1;
                            break;
                        }
                    }
                }
                if( icb )
                    dstp[x] = 255;
            }
        }
        mskp += msk_pitch;
        dmskpp += dmsk_pitch;
        dmskp += dmsk_pitch;
        dmskpn += dmsk_pitch;
        dstp += dst_pitch;
    }
}