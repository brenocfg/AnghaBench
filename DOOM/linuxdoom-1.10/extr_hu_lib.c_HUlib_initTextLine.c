#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  patch_t ;
struct TYPE_4__ {int x; int y; int sc; int /*<<< orphan*/ ** f; } ;
typedef  TYPE_1__ hu_textline_t ;

/* Variables and functions */
 int /*<<< orphan*/  HUlib_clearTextLine (TYPE_1__*) ; 

void
HUlib_initTextLine
( hu_textline_t*	t,
  int			x,
  int			y,
  patch_t**		f,
  int			sc )
{
    t->x = x;
    t->y = y;
    t->f = f;
    t->sc = sc;
    HUlib_clearTextLine(t);
}