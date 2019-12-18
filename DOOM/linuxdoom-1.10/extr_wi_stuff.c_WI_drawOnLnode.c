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
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  topoffset; int /*<<< orphan*/  leftoffset; } ;
typedef  TYPE_1__ patch_t ;
typedef  int boolean ;
struct TYPE_8__ {int x; int y; } ;
struct TYPE_7__ {size_t epsd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB ; 
 int SCREENHEIGHT ; 
 int SCREENWIDTH ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_DrawPatch (int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_3__** lnodes ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_2__* wbs ; 

void
WI_drawOnLnode
( int		n,
  patch_t*	c[] )
{

    int		i;
    int		left;
    int		top;
    int		right;
    int		bottom;
    boolean	fits = false;

    i = 0;
    do
    {
	left = lnodes[wbs->epsd][n].x - SHORT(c[i]->leftoffset);
	top = lnodes[wbs->epsd][n].y - SHORT(c[i]->topoffset);
	right = left + SHORT(c[i]->width);
	bottom = top + SHORT(c[i]->height);

	if (left >= 0
	    && right < SCREENWIDTH
	    && top >= 0
	    && bottom < SCREENHEIGHT)
	{
	    fits = true;
	}
	else
	{
	    i++;
	}
    } while (!fits && i!=2);

    if (fits && i<2)
    {
	V_DrawPatch(lnodes[wbs->epsd][n].x, lnodes[wbs->epsd][n].y,
		    FB, c[i]);
    }
    else
    {
	// DEBUG
	printf("Could not place patch on level %d", n+1); 
    }
}