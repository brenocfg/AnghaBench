#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int id; } ;
typedef  TYPE_3__ menucommon_s ;
struct TYPE_12__ {size_t curvalue; } ;
struct TYPE_11__ {int /*<<< orphan*/  leaguename; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {TYPE_1__ field; } ;
struct TYPE_10__ {TYPE_6__ list; TYPE_2__ rankname; } ;

/* Variables and functions */
#define  ID_SPECIFYLEAGUEBACK 132 
#define  ID_SPECIFYLEAGUEDOWN 131 
#define  ID_SPECIFYLEAGUELIST 130 
#define  ID_SPECIFYLEAGUENAME 129 
#define  ID_SPECIFYLEAGUEUP 128 
 int /*<<< orphan*/  K_DOWNARROW ; 
 int /*<<< orphan*/  K_UPARROW ; 
 int QM_ACTIVATED ; 
 int QM_GOTFOCUS ; 
 int QM_LOSTFOCUS ; 
 int /*<<< orphan*/  Q_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScrollList_Key (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpecifyLeague_GetList () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_5__* league_table ; 
 int /*<<< orphan*/  playername ; 
 TYPE_4__ s_specifyleague ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SpecifyLeague_Event( void* ptr, int event )
{
	int		id;
	id = ((menucommon_s*)ptr)->id;
	//if( event != QM_ACTIVATED && id != ID_SPECIFYLEAGUELIST ) {
	//	return;
	//}

	switch (id)
	{
		case ID_SPECIFYLEAGUELIST:
			if( event == QM_GOTFOCUS ) {
				//ArenaServers_UpdatePicture();
			}
		break;

		case ID_SPECIFYLEAGUEUP:
			if( event == QM_ACTIVATED )
				ScrollList_Key( &s_specifyleague.list, K_UPARROW );
		break;		
	
		case ID_SPECIFYLEAGUEDOWN:
			if( event == QM_ACTIVATED )
				ScrollList_Key( &s_specifyleague.list, K_DOWNARROW );
		break;
			
		case ID_SPECIFYLEAGUENAME:
			if( (event == QM_LOSTFOCUS) && 
				(Q_strncmp(playername, 
					s_specifyleague.rankname.field.buffer, 
					strlen(s_specifyleague.rankname.field.buffer)) != 0))
			{
				SpecifyLeague_GetList();
			}
		break;

		case ID_SPECIFYLEAGUEBACK:
			if( event == QM_ACTIVATED )
			{
				trap_Cvar_Set( "sv_leagueName", league_table[s_specifyleague.list.curvalue].leaguename);
				UI_PopMenu();
			}
		break;
	}
}