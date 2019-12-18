#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_7__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;
struct TYPE_9__ {int /*<<< orphan*/  cursor; } ;
struct TYPE_8__ {int modelpage; TYPE_3__ menu; int /*<<< orphan*/  numpages; int /*<<< orphan*/  nummodels; } ;

/* Variables and functions */
 int ID_PLAYERPIC0 ; 
#define  K_ESCAPE 133 
#define  K_KP_LEFTARROW 132 
#define  K_KP_RIGHTARROW 131 
#define  K_LEFTARROW 130 
#define  K_MOUSE2 129 
#define  K_RIGHTARROW 128 
 int MAX_MODELSPERPAGE ; 
 int /*<<< orphan*/  Menu_DefaultKey (TYPE_3__*,int) ; 
 TYPE_1__* Menu_ItemAtCursor (TYPE_3__*) ; 
 int /*<<< orphan*/  Menu_SetCursor (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlayerModel_SaveChanges () ; 
 int /*<<< orphan*/  PlayerModel_UpdateGrid () ; 
 int /*<<< orphan*/  menu_buzz_sound ; 
 int /*<<< orphan*/  menu_move_sound ; 
 TYPE_2__ s_playermodel ; 

__attribute__((used)) static sfxHandle_t PlayerModel_MenuKey( int key )
{
	menucommon_s*	m;
	int				picnum;

	switch (key)
	{
		case K_KP_LEFTARROW:
		case K_LEFTARROW:
			m = Menu_ItemAtCursor(&s_playermodel.menu);
			picnum = m->id - ID_PLAYERPIC0;
			if (picnum >= 0 && picnum <= 15)
			{
				if (picnum > 0)
				{
					Menu_SetCursor(&s_playermodel.menu,s_playermodel.menu.cursor-1);
					return (menu_move_sound);
					
				}
				else if (s_playermodel.modelpage > 0)
				{
					s_playermodel.modelpage--;
					Menu_SetCursor(&s_playermodel.menu,s_playermodel.menu.cursor+15);
					PlayerModel_UpdateGrid();
					return (menu_move_sound);
				}
				else
					return (menu_buzz_sound);
			}
			break;

		case K_KP_RIGHTARROW:
		case K_RIGHTARROW:
			m = Menu_ItemAtCursor(&s_playermodel.menu);
			picnum = m->id - ID_PLAYERPIC0;
			if (picnum >= 0 && picnum <= 15)
			{
				if ((picnum < 15) && (s_playermodel.modelpage*MAX_MODELSPERPAGE + picnum+1 < s_playermodel.nummodels))
				{
					Menu_SetCursor(&s_playermodel.menu,s_playermodel.menu.cursor+1);
					return (menu_move_sound);
				}					
				else if ((picnum == 15) && (s_playermodel.modelpage < s_playermodel.numpages-1))
				{
					s_playermodel.modelpage++;
					Menu_SetCursor(&s_playermodel.menu,s_playermodel.menu.cursor-15);
					PlayerModel_UpdateGrid();
					return (menu_move_sound);
				}
				else
					return (menu_buzz_sound);
			}
			break;
			
		case K_MOUSE2:
		case K_ESCAPE:
			PlayerModel_SaveChanges();
			break;
	}

	return ( Menu_DefaultKey( &s_playermodel.menu, key ) );
}