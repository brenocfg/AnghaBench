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
typedef  scalar_t__ fixed_t ;
struct TYPE_3__ {scalar_t__ dx; scalar_t__ x; scalar_t__ dy; scalar_t__ y; } ;
typedef  TYPE_1__ divline_t ;

/* Variables and functions */
 scalar_t__ FixedMul (scalar_t__,int) ; 

int
P_PointOnDivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	line )
{
    fixed_t	dx;
    fixed_t	dy;
    fixed_t	left;
    fixed_t	right;
	
    if (!line->dx)
    {
	if (x <= line->x)
	    return line->dy > 0;
	
	return line->dy < 0;
    }
    if (!line->dy)
    {
	if (y <= line->y)
	    return line->dx < 0;

	return line->dx > 0;
    }
	
    dx = (x - line->x);
    dy = (y - line->y);
	
    // try to quickly decide by looking at sign bits
    if ( (line->dy ^ line->dx ^ dx ^ dy)&0x80000000 )
    {
	if ( (line->dy ^ dx) & 0x80000000 )
	    return 1;		// (left is negative)
	return 0;
    }
	
    left = FixedMul ( line->dy>>8, dx>>8 );
    right = FixedMul ( dy>>8 , line->dx>>8 );
	
    if (right < left)
	return 0;		// front side
    return 1;			// back side
}