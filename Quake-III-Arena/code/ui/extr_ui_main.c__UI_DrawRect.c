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

/* Variables and functions */
 int /*<<< orphan*/  _UI_DrawSides (float,float,float,float,float) ; 
 int /*<<< orphan*/  _UI_DrawTopBottom (float,float,float,float,float) ; 
 int /*<<< orphan*/  trap_R_SetColor (float const*) ; 

void _UI_DrawRect( float x, float y, float width, float height, float size, const float *color ) {
	trap_R_SetColor( color );

  _UI_DrawTopBottom(x, y, width, height, size);
  _UI_DrawSides(x, y, width, height, size);

	trap_R_SetColor( NULL );
}