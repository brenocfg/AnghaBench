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
typedef  int /*<<< orphan*/  hu_textline_t ;
struct TYPE_3__ {int h; int cl; int /*<<< orphan*/ * l; int /*<<< orphan*/ * on; } ;
typedef  TYPE_1__ hu_stext_t ;

/* Variables and functions */
 int /*<<< orphan*/  HUlib_drawTextLine (int /*<<< orphan*/ *,int) ; 

void HUlib_drawSText(hu_stext_t* s)
{
    int i, idx;
    hu_textline_t *l;

    if (!*s->on)
	return; // if not on, don't draw

    // draw everything
    for (i=0 ; i<s->h ; i++)
    {
	idx = s->cl - i;
	if (idx < 0)
	    idx += s->h; // handle queue of lines
	
	l = &s->l[idx];

	// need a decision made here on whether to skip the draw
	HUlib_drawTextLine(l, false); // no cursor, please
    }

}