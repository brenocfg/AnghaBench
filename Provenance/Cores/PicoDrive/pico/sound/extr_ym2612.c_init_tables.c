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
typedef  int UINT8 ;
typedef  int UINT32 ;

/* Variables and functions */
 int ENV_STEP ; 
 int M_PI ; 
 int SIN_LEN ; 
 int TL_RES_LEN ; 
 double floor (double) ; 
 scalar_t__** lfo_pm_output ; 
 int* lfo_pm_table ; 
 int log (int) ; 
 int pow (int,int) ; 
 double sin (int) ; 
 int* ym_sin_tab ; 
 int* ym_tl_tab ; 
 int* ym_tl_tab2 ; 

__attribute__((used)) static void init_tables(void)
{
	signed int i,x,y,p;
	signed int n;
	double o,m;

	for (i=0; i < 256; i++)
	{
		/* non-standard sinus */
		m = sin( ((i*2)+1) * M_PI / SIN_LEN ); /* checked against the real chip */

		/* we never reach zero here due to ((i*2)+1) */

		if (m>0.0)
			o = 8*log(1.0/m)/log(2);	/* convert to 'decibels' */
		else
			o = 8*log(-1.0/m)/log(2);	/* convert to 'decibels' */

		o = o / (ENV_STEP/4);

		n = (int)(2.0*o);
		if (n&1)						/* round to nearest */
			n = (n>>1)+1;
		else
			n = n>>1;

		ym_sin_tab[ i ] = n;
		//dprintf("FM.C: sin [%4i]= %4i", i, ym_sin_tab[i]);
	}

	//dprintf("FM.C: ENV_QUIET= %08x", ENV_QUIET );


	for (x=0; x < TL_RES_LEN; x++)
	{
		m = (1<<16) / pow(2, (x+1) * (ENV_STEP/4.0) / 8.0);
		m = floor(m);

		/* we never reach (1<<16) here due to the (x+1) */
		/* result fits within 16 bits at maximum */

		n = (int)m;		/* 16 bits here */
		n >>= 4;		/* 12 bits here */
		if (n&1)		/* round to nearest */
			n = (n>>1)+1;
		else
			n = n>>1;
						/* 11 bits here (rounded) */
		n <<= 2;		/* 13 bits here (as in real chip) */
		ym_tl_tab2[ x ] = n;

		for (i=1; i < 13; i++)
		{
			ym_tl_tab2[ x + i*TL_RES_LEN ] = n >> i;
		}
	}

	for (x=0; x < 256; x++)
	{
		int sin = ym_sin_tab[ x ];

		for (y=0; y < 2*13*TL_RES_LEN/8; y+=2)
		{
			p = (y<<2) + sin;
			if (p >= 13*TL_RES_LEN)
				 ym_tl_tab[(y<<7) | x] = 0;
			else ym_tl_tab[(y<<7) | x] = ym_tl_tab2[p];
		}
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
				lfo_pm_table[(fnum*32*8) + (i*32) + step   + 0] = value;
				lfo_pm_table[(fnum*32*8) + (i*32) +(step^7)+ 8] = value;
				lfo_pm_table[(fnum*32*8) + (i*32) + step   +16] = -value;
				lfo_pm_table[(fnum*32*8) + (i*32) +(step^7)+24] = -value;
			}
		}
	}
}