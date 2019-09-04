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
struct TYPE_3__ {long x; long y; } ;
typedef  TYPE_1__ FT_Vector ;
typedef  int FT_Int ;
typedef  long FT_Fixed ;

/* Variables and functions */

__attribute__((used)) static FT_Int
  ft_trig_prenorm( FT_Vector*  vec )
  {
    FT_Fixed  x, y, z;
    FT_Int    shift;


    x = vec->x;
    y = vec->y;

    z     = ( ( x >= 0 ) ? x : - x ) | ( (y >= 0) ? y : -y );
    shift = 0;

#if 1
    /* determine msb bit index in `shift' */
    if ( z >= ( 1L << 16 ) )
    {
      z     >>= 16;
      shift  += 16;
    }
    if ( z >= ( 1L << 8 ) )
    {
      z     >>= 8;
      shift  += 8;
    }
    if ( z >= ( 1L << 4 ) )
    {
      z     >>= 4;
      shift  += 4;
    }
    if ( z >= ( 1L << 2 ) )
    {
      z     >>= 2;
      shift  += 2;
    }
    if ( z >= ( 1L << 1 ) )
    {
      z    >>= 1;
      shift += 1;
    }

    if ( shift <= 27 )
    {
      shift  = 27 - shift;
      vec->x = x << shift;
      vec->y = y << shift;
    }
    else
    {
      shift -= 27;
      vec->x = x >> shift;
      vec->y = y >> shift;
      shift  = -shift;
    }

#else /* 0 */

    if ( z < ( 1L << 27 ) )
    {
      do
      {
        shift++;
        z <<= 1;
      } while ( z < ( 1L << 27 ) );
      vec->x = x << shift;
      vec->y = y << shift;
    }
    else if ( z > ( 1L << 28 ) )
    {
      do
      {
        shift++;
        z >>= 1;
      } while ( z > ( 1L << 28 ) );

      vec->x = x >> shift;
      vec->y = y >> shift;
      shift  = -shift;
    }

#endif /* 0 */

    return shift;
  }