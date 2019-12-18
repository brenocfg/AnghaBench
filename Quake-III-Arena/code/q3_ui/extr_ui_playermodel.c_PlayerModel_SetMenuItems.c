#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* string; } ;
struct TYPE_6__ {char* string; } ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;
struct TYPE_8__ {int nummodels; char** modelnames; int selectedmodel; int modelpage; TYPE_3__ skinname; TYPE_2__ modelname; int /*<<< orphan*/  modelskin; TYPE_1__ playername; } ;

/* Variables and functions */
 int MAX_MODELSPERPAGE ; 
 int /*<<< orphan*/  Q_CleanStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  Q_strupr (char*) ; 
 TYPE_4__ s_playermodel ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void PlayerModel_SetMenuItems( void )
{
	int				i;
	int				maxlen;
	char			modelskin[64];
	char*			buffptr;
	char*			pdest;

	// name
	trap_Cvar_VariableStringBuffer( "name", s_playermodel.playername.string, 16 );
	Q_CleanStr( s_playermodel.playername.string );

	// model
	trap_Cvar_VariableStringBuffer( "model", s_playermodel.modelskin, 64 );
	
	// find model in our list
	for (i=0; i<s_playermodel.nummodels; i++)
	{
		// strip icon_
		buffptr  = s_playermodel.modelnames[i] + strlen("models/players/");
		pdest    = strstr(buffptr,"icon_");
		if (pdest)
		{
			Q_strncpyz(modelskin,buffptr,pdest-buffptr+1);
			strcat(modelskin,pdest + 5);
		}
		else
			continue;

		if (!Q_stricmp( s_playermodel.modelskin, modelskin ))
		{
			// found pic, set selection here		
			s_playermodel.selectedmodel = i;
			s_playermodel.modelpage     = i/MAX_MODELSPERPAGE;

			// seperate the model name
			maxlen = pdest-buffptr;
			if (maxlen > 16)
				maxlen = 16;
			Q_strncpyz( s_playermodel.modelname.string, buffptr, maxlen );
			Q_strupr( s_playermodel.modelname.string );

			// seperate the skin name
			maxlen = strlen(pdest+5)+1;
			if (maxlen > 16)
				maxlen = 16;
			Q_strncpyz( s_playermodel.skinname.string, pdest+5, maxlen );
			Q_strupr( s_playermodel.skinname.string );
			break;
		}
	}
}