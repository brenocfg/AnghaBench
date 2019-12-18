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
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  (* callback ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int curvalue; TYPE_1__ generic; } ;
typedef  TYPE_2__ menuradiobutton_s ;

/* Variables and functions */
#define  K_ENTER 138 
#define  K_JOY1 137 
#define  K_JOY2 136 
#define  K_JOY3 135 
#define  K_JOY4 134 
#define  K_KP_ENTER 133 
#define  K_KP_LEFTARROW 132 
#define  K_KP_RIGHTARROW 131 
#define  K_LEFTARROW 130 
#define  K_MOUSE1 129 
#define  K_RIGHTARROW 128 
 int QMF_HASMOUSEFOCUS ; 
 int /*<<< orphan*/  QM_ACTIVATED ; 
 int /*<<< orphan*/  menu_move_sound ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sfxHandle_t RadioButton_Key( menuradiobutton_s *rb, int key )
{
	switch (key)
	{
		case K_MOUSE1:
			if (!(rb->generic.flags & QMF_HASMOUSEFOCUS))
				break;

		case K_JOY1:
		case K_JOY2:
		case K_JOY3:
		case K_JOY4:
		case K_ENTER:
		case K_KP_ENTER:
		case K_KP_LEFTARROW:
		case K_LEFTARROW:
		case K_KP_RIGHTARROW:
		case K_RIGHTARROW:
			rb->curvalue = !rb->curvalue;
			if ( rb->generic.callback )
				rb->generic.callback( rb, QM_ACTIVATED );

			return (menu_move_sound);
	}

	// key not handled
	return 0;
}