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
typedef  int FT_Long ;
typedef  int FT_Byte ;

/* Variables and functions */
 int cff_parse_integer (int*,int*) ; 
 int cff_parse_real (int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static FT_Long
  cff_parse_num( FT_Byte**  d )
  {
    return **d == 30 ? ( cff_parse_real( d[0], d[1], 0, NULL ) >> 16 )
                     :   cff_parse_integer( d[0], d[1] );
  }