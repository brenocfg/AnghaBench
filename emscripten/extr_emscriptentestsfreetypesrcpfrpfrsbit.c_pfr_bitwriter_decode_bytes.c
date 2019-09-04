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
struct TYPE_3__ {int width; int total; scalar_t__* line; int /*<<< orphan*/  pitch; } ;
typedef  TYPE_1__* PFR_BitWriter ;
typedef  int FT_UInt ;
typedef  int FT_Int ;
typedef  scalar_t__ FT_Byte ;

/* Variables and functions */

__attribute__((used)) static void
  pfr_bitwriter_decode_bytes( PFR_BitWriter  writer,
                              FT_Byte*       p,
                              FT_Byte*       limit )
  {
    FT_Int    n, reload;
    FT_Int    left = writer->width;
    FT_Byte*  cur  = writer->line;
    FT_UInt   mask = 0x80;
    FT_UInt   val  = 0;
    FT_UInt   c    = 0;


    n = (FT_Int)( limit - p ) * 8;
    if ( n > writer->total )
      n = writer->total;

    reload = n & 7;

    for ( ; n > 0; n-- )
    {
      if ( ( n & 7 ) == reload )
        val = *p++;

      if ( val & 0x80 )
        c |= mask;

      val  <<= 1;
      mask >>= 1;

      if ( --left <= 0 )
      {
        cur[0] = (FT_Byte)c;
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
    }

    if ( mask != 0x80 )
      cur[0] = (FT_Byte)c;
  }