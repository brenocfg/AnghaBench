#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/ ** dt_tab; } ;
struct TYPE_5__ {TYPE_1__ ST; } ;
struct TYPE_6__ {TYPE_2__ OPN; } ;
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 double ENV_STEP ; 
 int M_PI ; 
 int SIN_LEN ; 
 int TL_RES_LEN ; 
 scalar_t__* dt_tab ; 
 double floor (double) ; 
 scalar_t__** lfo_pm_output ; 
 int* lfo_pm_table ; 
 int log (int) ; 
 int pow (int,int) ; 
 double sin (int) ; 
 int* sin_tab ; 
 int* tl_tab ; 
 TYPE_3__ ym2612 ; 

__attribute__((used)) static void init_tables(void)
{
  signed int d,i,x;
  signed int n;
  double o,m;

  /* build Linear Power Table */
  for (x=0; x<TL_RES_LEN; x++)
  {
    m = (1<<16) / pow(2,(x+1) * (ENV_STEP/4.0) / 8.0);
    m = floor(m);

    /* we never reach (1<<16) here due to the (x+1) */
    /* result fits within 16 bits at maximum */

    n = (int)m; /* 16 bits here */
    n >>= 4;    /* 12 bits here */
    if (n&1)    /* round to nearest */
      n = (n>>1)+1;
    else
      n = n>>1;
                /* 11 bits here (rounded) */
    n <<= 2;    /* 13 bits here (as in real chip) */

    /* 14 bits (with sign bit) */
    tl_tab[ x*2 + 0 ] = n;
    tl_tab[ x*2 + 1 ] = -tl_tab[ x*2 + 0 ];

    /* one entry in the 'Power' table use the following format, xxxxxyyyyyyyys with:            */
    /*        s = sign bit                                                                      */
    /* yyyyyyyy = 8-bits decimal part (0-TL_RES_LEN)                                            */
    /* xxxxx    = 5-bits integer 'shift' value (0-31) but, since Power table output is 13 bits, */
    /*            any value above 13 (included) would be discarded.                             */
    for (i=1; i<13; i++)
    {
      tl_tab[ x*2+0 + i*2*TL_RES_LEN ] =  tl_tab[ x*2+0 ]>>i;
      tl_tab[ x*2+1 + i*2*TL_RES_LEN ] = -tl_tab[ x*2+0 + i*2*TL_RES_LEN ];
    }
  }

  /* build Logarithmic Sinus table */
  for (i=0; i<SIN_LEN; i++)
  {
    /* non-standard sinus */
    m = sin( ((i*2)+1) * M_PI / SIN_LEN ); /* checked against the real chip */
    /* we never reach zero here due to ((i*2)+1) */

    if (m>0.0)
      o = 8*log(1.0/m)/log(2);  /* convert to 'decibels' */
    else
      o = 8*log(-1.0/m)/log(2);  /* convert to 'decibels' */

    o = o / (ENV_STEP/4);

    n = (int)(2.0*o);
    if (n&1)            /* round to nearest */
      n = (n>>1)+1;
    else
      n = n>>1;

    /* 13-bits (8.5) value is formatted for above 'Power' table */
    sin_tab[ i ] = n*2 + (m>=0.0? 0: 1 );
  }

  /* build LFO PM modulation table */
  for(i = 0; i < 8; i++) /* 8 PM depths */
  {
    UINT8 fnum;
    for (fnum=0; fnum<128; fnum++) /* 7 bits meaningful of F-NUMBER */
    {
      UINT8 value;
      UINT8 step;
      UINT32 offset_depth = i;
      UINT32 offset_fnum_bit;
      UINT32 bit_tmp;

      for (step=0; step<8; step++) 
      {
        value = 0;
        for (bit_tmp=0; bit_tmp<7; bit_tmp++) /* 7 bits */
        {
          if (fnum & (1<<bit_tmp)) /* only if bit "bit_tmp" is set */
          {
            offset_fnum_bit = bit_tmp * 8;
            value += lfo_pm_output[offset_fnum_bit + offset_depth][step];
          }
        }
        /* 32 steps for LFO PM (sinus) */
        lfo_pm_table[(fnum*32*8) + (i*32) + step   + 0] = value;
        lfo_pm_table[(fnum*32*8) + (i*32) +(step^7)+ 8] = value;
        lfo_pm_table[(fnum*32*8) + (i*32) + step   +16] = -value;
        lfo_pm_table[(fnum*32*8) + (i*32) +(step^7)+24] = -value;
      }
    }
  }

  /* build DETUNE table */
  for (d = 0;d <= 3;d++)
  {
    for (i = 0;i <= 31;i++)
    {
      ym2612.OPN.ST.dt_tab[d][i]   = (INT32) dt_tab[d*32 + i];
      ym2612.OPN.ST.dt_tab[d+4][i] = -ym2612.OPN.ST.dt_tab[d][i];
    }
  }

}