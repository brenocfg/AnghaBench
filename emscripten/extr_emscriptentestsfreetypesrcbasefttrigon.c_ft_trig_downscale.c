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
typedef  int FT_UInt32 ;
typedef  int FT_Fixed ;

/* Variables and functions */
 int FT_TRIG_SCALE ; 

__attribute__((used)) static FT_Fixed
  ft_trig_downscale( FT_Fixed  val )
  {
    FT_Fixed   s;
    FT_UInt32  v1, v2, k1, k2, hi, lo1, lo2, lo3;


    s   = val;
    val = ( val >= 0 ) ? val : -val;

    v1 = (FT_UInt32)val >> 16;
    v2 = (FT_UInt32)(val & 0xFFFFL);

    k1 = (FT_UInt32)FT_TRIG_SCALE >> 16;       /* constant */
    k2 = (FT_UInt32)(FT_TRIG_SCALE & 0xFFFFL);   /* constant */

    hi   = k1 * v1;
    lo1  = k1 * v2 + k2 * v1;       /* can't overflow */

    lo2  = ( k2 * v2 ) >> 16;
    lo3  = ( lo1 >= lo2 ) ? lo1 : lo2;
    lo1 += lo2;

    hi  += lo1 >> 16;
    if ( lo1 < lo3 )
      hi += (FT_UInt32)0x10000UL;

    val  = (FT_Fixed)hi;

    return ( s >= 0 ) ? val : -val;
  }