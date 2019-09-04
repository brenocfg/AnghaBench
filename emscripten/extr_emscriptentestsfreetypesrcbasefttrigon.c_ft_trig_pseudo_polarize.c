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
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ FT_Vector ;
typedef  int FT_Fixed ;

/* Variables and functions */
 int FT_ANGLE_PI2 ; 
 int FT_PAD_ROUND (int,int) ; 
 int FT_TRIG_MAX_ITERS ; 
 int* ft_trig_arctan_table ; 

__attribute__((used)) static void
  ft_trig_pseudo_polarize( FT_Vector*  vec )
  {
    FT_Fixed         theta;
    FT_Fixed         yi, i;
    FT_Fixed         x, y;
    const FT_Fixed  *arctanptr;


    x = vec->x;
    y = vec->y;

    /* Get the vector into the right half plane */
    theta = 0;
    if ( x < 0 )
    {
      x = -x;
      y = -y;
      theta = 2 * FT_ANGLE_PI2;
    }

    if ( y > 0 )
      theta = - theta;

    arctanptr = ft_trig_arctan_table;

    if ( y < 0 )
    {
      /* Rotate positive */
      yi     = y + ( x << 1 );
      x      = x - ( y << 1 );
      y      = yi;
      theta -= *arctanptr++;  /* Subtract angle */
    }
    else
    {
      /* Rotate negative */
      yi     = y - ( x << 1 );
      x      = x + ( y << 1 );
      y      = yi;
      theta += *arctanptr++;  /* Add angle */
    }

    i = 0;
    do
    {
      if ( y < 0 )
      {
        /* Rotate positive */
        yi     = y + ( x >> i );
        x      = x - ( y >> i );
        y      = yi;
        theta -= *arctanptr++;
      }
      else
      {
        /* Rotate negative */
        yi     = y - ( x >> i );
        x      = x + ( y >> i );
        y      = yi;
        theta += *arctanptr++;
      }
    } while ( ++i < FT_TRIG_MAX_ITERS );

    /* round theta */
    if ( theta >= 0 )
      theta = FT_PAD_ROUND( theta, 32 );
    else
      theta = -FT_PAD_ROUND( -theta, 32 );

    vec->x = x;
    vec->y = theta;
  }