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
typedef  scalar_t__ FT_Int ;
typedef  int FT_Fixed ;
typedef  int /*<<< orphan*/  FT_Angle ;

/* Variables and functions */
 scalar_t__ FT_ANGLE_PI ; 
 int /*<<< orphan*/  FT_ANGLE_PI2 ; 
 scalar_t__ FT_TRIG_MAX_ITERS ; 
 int* ft_trig_arctan_table ; 

__attribute__((used)) static void
  ft_trig_pseudo_rotate( FT_Vector*  vec,
                         FT_Angle    theta )
  {
    FT_Int           i;
    FT_Fixed         x, y, xtemp;
    const FT_Fixed  *arctanptr;


    x = vec->x;
    y = vec->y;

    /* Get angle between -90 and 90 degrees */
    while ( theta <= -FT_ANGLE_PI2 )
    {
      x = -x;
      y = -y;
      theta += FT_ANGLE_PI;
    }

    while ( theta > FT_ANGLE_PI2 )
    {
      x = -x;
      y = -y;
      theta -= FT_ANGLE_PI;
    }

    /* Initial pseudorotation, with left shift */
    arctanptr = ft_trig_arctan_table;

    if ( theta < 0 )
    {
      xtemp  = x + ( y << 1 );
      y      = y - ( x << 1 );
      x      = xtemp;
      theta += *arctanptr++;
    }
    else
    {
      xtemp  = x - ( y << 1 );
      y      = y + ( x << 1 );
      x      = xtemp;
      theta -= *arctanptr++;
    }

    /* Subsequent pseudorotations, with right shifts */
    i = 0;
    do
    {
      if ( theta < 0 )
      {
        xtemp  = x + ( y >> i );
        y      = y - ( x >> i );
        x      = xtemp;
        theta += *arctanptr++;
      }
      else
      {
        xtemp  = x - ( y >> i );
        y      = y + ( x >> i );
        x      = xtemp;
        theta -= *arctanptr++;
      }
    } while ( ++i < FT_TRIG_MAX_ITERS );

    vec->x = x;
    vec->y = y;
  }