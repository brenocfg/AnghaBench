#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* widths; } ;
struct TYPE_7__ {TYPE_2__ stdw; } ;
struct TYPE_5__ {int cur; } ;
typedef  TYPE_3__* PSH_Dimension ;
typedef  int FT_Pos ;
typedef  scalar_t__ FT_Bool ;

/* Variables and functions */
 int FT_PIX_ROUND (int) ; 

__attribute__((used)) static FT_Pos
  psh_dimension_quantize_len( PSH_Dimension  dim,
                              FT_Pos         len,
                              FT_Bool        do_snapping )
  {
    if ( len <= 64 )
      len = 64;
    else
    {
      FT_Pos  delta = len - dim->stdw.widths[0].cur;


      if ( delta < 0 )
        delta = -delta;

      if ( delta < 40 )
      {
        len = dim->stdw.widths[0].cur;
        if ( len < 48 )
          len = 48;
      }

      if ( len < 3 * 64 )
      {
        delta = ( len & 63 );
        len  &= -64;

        if ( delta < 10 )
          len += delta;

        else if ( delta < 32 )
          len += 10;

        else if ( delta < 54 )
          len += 54;

        else
          len += delta;
      }
      else
        len = FT_PIX_ROUND( len );
    }

    if ( do_snapping )
      len = FT_PIX_ROUND( len );

    return  len;
  }