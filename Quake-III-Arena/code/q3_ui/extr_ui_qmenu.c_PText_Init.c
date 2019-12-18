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
struct TYPE_4__ {int x; int y; int flags; int left; int right; int top; int bottom; } ;
struct TYPE_5__ {TYPE_1__ generic; int /*<<< orphan*/  string; int /*<<< orphan*/  style; } ;
typedef  TYPE_2__ menutext_s ;

/* Variables and functions */
 float PROP_GAP_WIDTH ; 
 float PROP_HEIGHT ; 
 int QMF_CENTER_JUSTIFY ; 
 int QMF_RIGHT_JUSTIFY ; 
 float UI_ProportionalSizeScale (int /*<<< orphan*/ ) ; 
 float UI_ProportionalStringWidth (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PText_Init( menutext_s *t )
{
	int	x;
	int	y;
	int	w;
	int	h;
	float	sizeScale;

	sizeScale = UI_ProportionalSizeScale( t->style );

	x = t->generic.x;
	y = t->generic.y;
	w = UI_ProportionalStringWidth( t->string ) * sizeScale;
	h =	PROP_HEIGHT * sizeScale;

	if( t->generic.flags & QMF_RIGHT_JUSTIFY ) {
		x -= w;
	}
	else if( t->generic.flags & QMF_CENTER_JUSTIFY ) {
		x -= w / 2;
	}

	t->generic.left   = x - PROP_GAP_WIDTH * sizeScale;
	t->generic.right  = x + w + PROP_GAP_WIDTH * sizeScale;
	t->generic.top    = y;
	t->generic.bottom = y + h;
}