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
typedef  int /*<<< orphan*/  patch_t ;
struct TYPE_3__ {int laston; int /*<<< orphan*/  l; int /*<<< orphan*/ * on; scalar_t__ lm; } ;
typedef  TYPE_1__ hu_itext_t ;
typedef  int /*<<< orphan*/  boolean ;

/* Variables and functions */
 int /*<<< orphan*/  HUlib_initTextLine (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int) ; 

void
HUlib_initIText
( hu_itext_t*	it,
  int		x,
  int		y,
  patch_t**	font,
  int		startchar,
  boolean*	on )
{
    it->lm = 0; // default left margin is start of text
    it->on = on;
    it->laston = true;
    HUlib_initTextLine(&it->l, x, y, font, startchar);
}