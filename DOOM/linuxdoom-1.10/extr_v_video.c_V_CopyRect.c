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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*) ; 
 int SCREENHEIGHT ; 
 int SCREENWIDTH ; 
 int /*<<< orphan*/  V_MarkRect (int,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** screens ; 

void
V_CopyRect
( int		srcx,
  int		srcy,
  int		srcscrn,
  int		width,
  int		height,
  int		destx,
  int		desty,
  int		destscrn ) 
{ 
    byte*	src;
    byte*	dest; 
	 
#ifdef RANGECHECK 
    if (srcx<0
	||srcx+width >SCREENWIDTH
	|| srcy<0
	|| srcy+height>SCREENHEIGHT 
	||destx<0||destx+width >SCREENWIDTH
	|| desty<0
	|| desty+height>SCREENHEIGHT 
	|| (unsigned)srcscrn>4
	|| (unsigned)destscrn>4)
    {
	I_Error ("Bad V_CopyRect");
    }
#endif 
    V_MarkRect (destx, desty, width, height); 
	 
    src = screens[srcscrn]+SCREENWIDTH*srcy+srcx; 
    dest = screens[destscrn]+SCREENWIDTH*desty+destx; 

    for ( ; height>0 ; height--) 
    { 
	memcpy (dest, src, width); 
	src += SCREENWIDTH; 
	dest += SCREENWIDTH; 
    } 
}