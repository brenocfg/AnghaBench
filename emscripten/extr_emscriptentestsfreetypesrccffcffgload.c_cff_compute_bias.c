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
typedef  int FT_UInt ;
typedef  int FT_Int ;

/* Variables and functions */

__attribute__((used)) static FT_Int
  cff_compute_bias( FT_Int   in_charstring_type,
                    FT_UInt  num_subrs )
  {
    FT_Int  result;


    if ( in_charstring_type == 1 )
      result = 0;
    else if ( num_subrs < 1240 )
      result = 107;
    else if ( num_subrs < 33900U )
      result = 1131;
    else
      result = 32768U;

    return result;
  }