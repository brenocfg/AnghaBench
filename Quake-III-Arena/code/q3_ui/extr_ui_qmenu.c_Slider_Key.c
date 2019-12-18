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
typedef  scalar_t__ sfxHandle_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* callback ) (TYPE_2__*,int /*<<< orphan*/ ) ;scalar_t__ x; } ;
struct TYPE_7__ {int curvalue; int maxvalue; int minvalue; TYPE_1__ generic; } ;
typedef  TYPE_2__ menuslider_s ;
struct TYPE_8__ {scalar_t__ cursorx; } ;

/* Variables and functions */
#define  K_KP_LEFTARROW 132 
#define  K_KP_RIGHTARROW 131 
#define  K_LEFTARROW 130 
#define  K_MOUSE1 129 
#define  K_RIGHTARROW 128 
 int /*<<< orphan*/  QM_ACTIVATED ; 
 int SLIDER_RANGE ; 
 int SMALLCHAR_WIDTH ; 
 scalar_t__ menu_buzz_sound ; 
 scalar_t__ menu_move_sound ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ uis ; 

__attribute__((used)) static sfxHandle_t Slider_Key( menuslider_s *s, int key )
{
	sfxHandle_t	sound;
	int			x;
	int			oldvalue;

	switch (key)
	{
		case K_MOUSE1:
			x           = uis.cursorx - s->generic.x - 2*SMALLCHAR_WIDTH;
			oldvalue    = s->curvalue;
			s->curvalue = (x/(float)(SLIDER_RANGE*SMALLCHAR_WIDTH)) * (s->maxvalue-s->minvalue) + s->minvalue;

			if (s->curvalue < s->minvalue)
				s->curvalue = s->minvalue;
			else if (s->curvalue > s->maxvalue)
				s->curvalue = s->maxvalue;
			if (s->curvalue != oldvalue)
				sound = menu_move_sound;
			else
				sound = 0;
			break;

		case K_KP_LEFTARROW:
		case K_LEFTARROW:
			if (s->curvalue > s->minvalue)
			{
				s->curvalue--;
				sound = menu_move_sound;
			}
			else
				sound = menu_buzz_sound;
			break;			

		case K_KP_RIGHTARROW:
		case K_RIGHTARROW:
			if (s->curvalue < s->maxvalue)
			{
				s->curvalue++;
				sound = menu_move_sound;
			}
			else
				sound = menu_buzz_sound;
			break;			

		default:
			// key not handled
			sound = 0;
			break;
	}

	if ( sound && s->generic.callback )
		s->generic.callback( s, QM_ACTIVATED );

	return (sound);
}