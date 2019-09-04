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
typedef  scalar_t__ FT_Fixed ;

/* Variables and functions */
 scalar_t__ FT_ABS (scalar_t__) ; 
 scalar_t__ FT_PIX_ROUND (scalar_t__) ; 

__attribute__((used)) static FT_Fixed
  psh_hint_snap_stem_side_delta( FT_Fixed  pos,
                                 FT_Fixed  len )
  {
    FT_Fixed  delta1 = FT_PIX_ROUND( pos ) - pos;
    FT_Fixed  delta2 = FT_PIX_ROUND( pos + len ) - pos - len;


    if ( FT_ABS( delta1 ) <= FT_ABS( delta2 ) )
      return delta1;
    else
      return delta2;
  }