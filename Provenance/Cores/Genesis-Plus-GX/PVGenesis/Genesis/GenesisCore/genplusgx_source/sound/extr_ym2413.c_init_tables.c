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

/* Variables and functions */
 double ENV_STEP ; 
 int M_PI ; 
 int SIN_BITS ; 
 int SIN_LEN ; 
 int TL_RES_LEN ; 
 int TL_TAB_LEN ; 
 double floor (double) ; 
 int log (int) ; 
 int pow (int,int) ; 
 double sin (int) ; 
 int* sin_tab ; 
 int* tl_tab ; 

__attribute__((used)) static int init_tables(void)
{
  signed int i,x;
  signed int n;
  double o,m;

  for (x=0; x<TL_RES_LEN; x++)
  {
    m = (1<<16) / pow(2, (x+1) * (ENV_STEP/4.0) / 8.0);
    m = floor(m);

    /* we never reach (1<<16) here due to the (x+1) */
    /* result fits within 16 bits at maximum */

    n = (int)m;    /* 16 bits here */
    n >>= 4;    /* 12 bits here */
    if (n&1)    /* round to nearest */
      n = (n>>1)+1;
    else
      n = n>>1;
            /* 11 bits here (rounded) */
    tl_tab[ x*2 + 0 ] = n;
    tl_tab[ x*2 + 1 ] = -tl_tab[ x*2 + 0 ];

    for (i=1; i<11; i++)
    {
      tl_tab[ x*2+0 + i*2*TL_RES_LEN ] =  tl_tab[ x*2+0 ]>>i;
      tl_tab[ x*2+1 + i*2*TL_RES_LEN ] = -tl_tab[ x*2+0 + i*2*TL_RES_LEN ];
    }
  }

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

    /* waveform 0: standard sinus  */
    sin_tab[ i ] = n*2 + (m>=0.0? 0: 1 );

    /* waveform 1:  __      __     */
    /*             /  \____/  \____*/
    /* output only first half of the sinus waveform (positive one) */
    if (i & (1<<(SIN_BITS-1)) )
      sin_tab[1*SIN_LEN+i] = TL_TAB_LEN;
    else
      sin_tab[1*SIN_LEN+i] = sin_tab[i];
  }

  return 1;
}