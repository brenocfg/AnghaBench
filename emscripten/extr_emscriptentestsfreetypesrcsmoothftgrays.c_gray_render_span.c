#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pitch; int rows; scalar_t__ buffer; } ;
struct TYPE_7__ {unsigned char coverage; int len; int x; } ;
struct TYPE_6__ {TYPE_3__ target; } ;
typedef  TYPE_1__* PWorker ;
typedef  TYPE_2__ FT_Span ;
typedef  TYPE_3__ FT_Bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  FT_MEM_SET (unsigned char*,unsigned char,int) ; 

__attribute__((used)) static void
  gray_render_span( int             y,
                    int             count,
                    const FT_Span*  spans,
                    PWorker         worker )
  {
    unsigned char*  p;
    FT_Bitmap*      map = &worker->target;


    /* first of all, compute the scanline offset */
    p = (unsigned char*)map->buffer - y * map->pitch;
    if ( map->pitch >= 0 )
      p += (unsigned)( ( map->rows - 1 ) * map->pitch );

    for ( ; count > 0; count--, spans++ )
    {
      unsigned char  coverage = spans->coverage;


      if ( coverage )
      {
        /* For small-spans it is faster to do it by ourselves than
         * calling `memset'.  This is mainly due to the cost of the
         * function call.
         */
        if ( spans->len >= 8 )
          FT_MEM_SET( p + spans->x, (unsigned char)coverage, spans->len );
        else
        {
          unsigned char*  q = p + spans->x;


          switch ( spans->len )
          {
          case 7: *q++ = (unsigned char)coverage;
          case 6: *q++ = (unsigned char)coverage;
          case 5: *q++ = (unsigned char)coverage;
          case 4: *q++ = (unsigned char)coverage;
          case 3: *q++ = (unsigned char)coverage;
          case 2: *q++ = (unsigned char)coverage;
          case 1: *q   = (unsigned char)coverage;
          default:
            ;
          }
        }
      }
    }
  }