#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  height; } ;
typedef  TYPE_1__ patch_t ;
struct TYPE_7__ {int h; int laston; int /*<<< orphan*/ * l; scalar_t__ cl; int /*<<< orphan*/ * on; } ;
typedef  TYPE_2__ hu_stext_t ;
typedef  int /*<<< orphan*/  boolean ;

/* Variables and functions */
 int /*<<< orphan*/  HUlib_initTextLine (int /*<<< orphan*/ *,int,int,TYPE_1__**,int) ; 
 int SHORT (int /*<<< orphan*/ ) ; 

void
HUlib_initSText
( hu_stext_t*	s,
  int		x,
  int		y,
  int		h,
  patch_t**	font,
  int		startchar,
  boolean*	on )
{

    int i;

    s->h = h;
    s->on = on;
    s->laston = true;
    s->cl = 0;
    for (i=0;i<h;i++)
	HUlib_initTextLine(&s->l[i],
			   x, y - i*(SHORT(font[0]->height)+1),
			   font, startchar);

}