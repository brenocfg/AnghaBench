#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ width; scalar_t__ total; scalar_t__* line; int /*<<< orphan*/  pitch; } ;
typedef  TYPE_1__* PFR_BitWriter ;
typedef  int FT_UInt ;
typedef  scalar_t__ FT_Int ;
typedef  scalar_t__ FT_Byte ;

/* Variables and functions */

__attribute__((used)) static void
  pfr_bitwriter_decode_rle1( PFR_BitWriter  writer,
                             FT_Byte*       p,
                             FT_Byte*       limit )
  {
    FT_Int    n, phase, count, counts[2], reload;
    FT_Int    left = writer->width;
    FT_Byte*  cur  = writer->line;
    FT_UInt   mask = 0x80;
    FT_UInt   c    = 0;


    n = writer->total;

    phase     = 1;
    counts[0] = 0;
    counts[1] = 0;
    count     = 0;
    reload    = 1;

    for ( ; n > 0; n-- )
    {
      if ( reload )
      {
        do
        {
          if ( phase )
          {
            FT_Int  v;


            if ( p >= limit )
              break;

            v         = *p++;
            counts[0] = v >> 4;
            counts[1] = v & 15;
            phase     = 0;
            count     = counts[0];
          }
          else
          {
            phase = 1;
            count = counts[1];
          }

        } while ( count == 0 );
      }

      if ( phase )
        c |= mask;

      mask >>= 1;

      if ( --left <= 0 )
      {
        cur[0] = (FT_Byte) c;
        left   = writer->width;
        mask   = 0x80;

        writer->line += writer->pitch;
        cur           = writer->line;
        c             = 0;
      }
      else if ( mask == 0 )
      {
        cur[0] = (FT_Byte)c;
        mask   = 0x80;
        c      = 0;
        cur ++;
      }

      reload = ( --count <= 0 );
    }

    if ( mask != 0x80 )
      cur[0] = (FT_Byte) c;
  }