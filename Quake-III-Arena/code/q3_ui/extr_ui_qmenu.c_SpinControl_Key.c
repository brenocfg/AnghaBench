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
typedef  scalar_t__ sfxHandle_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* callback ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ generic; int /*<<< orphan*/  curvalue; int /*<<< orphan*/  numitems; } ;
typedef  TYPE_2__ menulist_s ;

/* Variables and functions */
#define  K_KP_LEFTARROW 132 
#define  K_KP_RIGHTARROW 131 
#define  K_LEFTARROW 130 
#define  K_MOUSE1 129 
#define  K_RIGHTARROW 128 
 int /*<<< orphan*/  QM_ACTIVATED ; 
 scalar_t__ menu_buzz_sound ; 
 scalar_t__ menu_move_sound ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sfxHandle_t SpinControl_Key( menulist_s *s, int key )
{
	sfxHandle_t	sound;

	sound = 0;
	switch (key)
	{
		case K_MOUSE1:
			s->curvalue++;
			if (s->curvalue >= s->numitems)
				s->curvalue = 0;
			sound = menu_move_sound;
			break;
		
		case K_KP_LEFTARROW:
		case K_LEFTARROW:
			if (s->curvalue > 0)
			{
				s->curvalue--;
				sound = menu_move_sound;
			}
			else
				sound = menu_buzz_sound;
			break;

		case K_KP_RIGHTARROW:
		case K_RIGHTARROW:
			if (s->curvalue < s->numitems-1)
			{
				s->curvalue++;
				sound = menu_move_sound;
			}
			else
				sound = menu_buzz_sound;
			break;
	}

	if ( sound && s->generic.callback )
		s->generic.callback( s, QM_ACTIVATED );

	return (sound);
}