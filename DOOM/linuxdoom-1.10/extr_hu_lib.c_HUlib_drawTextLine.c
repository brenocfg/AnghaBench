#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int x; int len; unsigned char sc; TYPE_2__** f; int /*<<< orphan*/  y; int /*<<< orphan*/ * l; } ;
typedef  TYPE_1__ hu_textline_t ;
typedef  scalar_t__ boolean ;
struct TYPE_5__ {int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  FG ; 
 int SCREENWIDTH ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_DrawPatchDirect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 unsigned char toupper (int /*<<< orphan*/ ) ; 

void
HUlib_drawTextLine
( hu_textline_t*	l,
  boolean		drawcursor )
{

    int			i;
    int			w;
    int			x;
    unsigned char	c;

    // draw the new stuff
    x = l->x;
    for (i=0;i<l->len;i++)
    {
	c = toupper(l->l[i]);
	if (c != ' '
	    && c >= l->sc
	    && c <= '_')
	{
	    w = SHORT(l->f[c - l->sc]->width);
	    if (x+w > SCREENWIDTH)
		break;
	    V_DrawPatchDirect(x, l->y, FG, l->f[c - l->sc]);
	    x += w;
	}
	else
	{
	    x += 4;
	    if (x >= SCREENWIDTH)
		break;
	}
    }

    // draw the cursor if requested
    if (drawcursor
	&& x + SHORT(l->f['_' - l->sc]->width) <= SCREENWIDTH)
    {
	V_DrawPatchDirect(x, l->y, FG, l->f['_' - l->sc]);
    }
}