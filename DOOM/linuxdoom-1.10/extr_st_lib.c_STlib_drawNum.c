#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int* num; int x; int oldnum; scalar_t__ y; TYPE_2__** p; } ;
typedef  TYPE_1__ st_number_t ;
typedef  int /*<<< orphan*/  boolean ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG ; 
 int /*<<< orphan*/  FG ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ ST_Y ; 
 int /*<<< orphan*/  V_CopyRect (int,scalar_t__,int /*<<< orphan*/ ,int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_DrawPatch (int,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* sttminus ; 

void
STlib_drawNum
( st_number_t*	n,
  boolean	refresh )
{

    int		numdigits = n->width;
    int		num = *n->num;
    
    int		w = SHORT(n->p[0]->width);
    int		h = SHORT(n->p[0]->height);
    int		x = n->x;
    
    int		neg;

    n->oldnum = *n->num;

    neg = num < 0;

    if (neg)
    {
	if (numdigits == 2 && num < -9)
	    num = -9;
	else if (numdigits == 3 && num < -99)
	    num = -99;
	
	num = -num;
    }

    // clear the area
    x = n->x - numdigits*w;

    if (n->y - ST_Y < 0)
	I_Error("drawNum: n->y - ST_Y < 0");

    V_CopyRect(x, n->y - ST_Y, BG, w*numdigits, h, x, n->y, FG);

    // if non-number, do not draw it
    if (num == 1994)
	return;

    x = n->x;

    // in the special case of 0, you draw 0
    if (!num)
	V_DrawPatch(x - w, n->y, FG, n->p[ 0 ]);

    // draw the new number
    while (num && numdigits--)
    {
	x -= w;
	V_DrawPatch(x, n->y, FG, n->p[ num % 10 ]);
	num /= 10;
    }

    // draw a minus sign if necessary
    if (neg)
	V_DrawPatch(x - 8, n->y, FG, sttminus);
}