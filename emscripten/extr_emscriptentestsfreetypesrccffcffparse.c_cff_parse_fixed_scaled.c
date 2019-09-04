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
typedef  size_t FT_Long ;
typedef  int FT_Fixed ;
typedef  int FT_Byte ;

/* Variables and functions */
 int cff_parse_integer (int*,int*) ; 
 int cff_parse_real (int*,int*,size_t,int /*<<< orphan*/ *) ; 
 int* power_tens ; 

__attribute__((used)) static FT_Fixed
  cff_parse_fixed_scaled( FT_Byte**  d,
                          FT_Long    scaling )
  {
    return **d == 30 ? cff_parse_real( d[0], d[1], scaling, NULL )
                     : ( cff_parse_integer( d[0], d[1] ) *
                           power_tens[scaling] ) << 16;
  }