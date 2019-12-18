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
struct TYPE_4__ {int x; int y; int flags; } ;
struct TYPE_5__ {float* color; int /*<<< orphan*/  style; int /*<<< orphan*/  string; TYPE_1__ generic; } ;
typedef  TYPE_2__ menutext_s ;

/* Variables and functions */
 int QMF_GRAYED ; 
 int /*<<< orphan*/  UI_DrawBannerString (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 float* text_color_disabled ; 

__attribute__((used)) static void BText_Draw( menutext_s *t )
{
	int		x;
	int		y;
	float*	color;

	x = t->generic.x;
	y = t->generic.y;

	if (t->generic.flags & QMF_GRAYED)
		color = text_color_disabled;
	else
		color = t->color;

	UI_DrawBannerString( x, y, t->string, t->style, color );
}