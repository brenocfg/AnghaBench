#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_2__ {int nummodels; int numpages; int /*<<< orphan*/ * modelnames; scalar_t__ modelpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM_StripExtension (char*,char*) ; 
 int /*<<< orphan*/  Com_sprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int MAX_MODELSPERPAGE ; 
 int MAX_PLAYERMODELS ; 
 int /*<<< orphan*/  Q_stricmpn (char*,char*,int) ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_1__ s_playermodel ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int trap_FS_GetFileList (char*,char*,char*,int) ; 
 int /*<<< orphan*/  trap_S_RegisterSound (char*,int /*<<< orphan*/ ) ; 
 char* va (char*,char*) ; 

__attribute__((used)) static void PlayerModel_BuildList( void )
{
	int		numdirs;
	int		numfiles;
	char	dirlist[2048];
	char	filelist[2048];
	char	skinname[64];
	char*	dirptr;
	char*	fileptr;
	int		i;
	int		j;
	int		dirlen;
	int		filelen;
	qboolean precache;

	precache = trap_Cvar_VariableValue("com_buildscript");

	s_playermodel.modelpage = 0;
	s_playermodel.nummodels = 0;

	// iterate directory of all player models
	numdirs = trap_FS_GetFileList("models/players", "/", dirlist, 2048 );
	dirptr  = dirlist;
	for (i=0; i<numdirs && s_playermodel.nummodels < MAX_PLAYERMODELS; i++,dirptr+=dirlen+1)
	{
		dirlen = strlen(dirptr);
		
		if (dirlen && dirptr[dirlen-1]=='/') dirptr[dirlen-1]='\0';

		if (!strcmp(dirptr,".") || !strcmp(dirptr,".."))
			continue;
			
		// iterate all skin files in directory
		numfiles = trap_FS_GetFileList( va("models/players/%s",dirptr), "tga", filelist, 2048 );
		fileptr  = filelist;
		for (j=0; j<numfiles && s_playermodel.nummodels < MAX_PLAYERMODELS;j++,fileptr+=filelen+1)
		{
			filelen = strlen(fileptr);

			COM_StripExtension(fileptr,skinname);

			// look for icon_????
			if (!Q_stricmpn(skinname,"icon_",5))
			{
				Com_sprintf( s_playermodel.modelnames[s_playermodel.nummodels++],
					sizeof( s_playermodel.modelnames[s_playermodel.nummodels] ),
					"models/players/%s/%s", dirptr, skinname );
				//if (s_playermodel.nummodels >= MAX_PLAYERMODELS)
				//	return;
			}

			if( precache ) {
				trap_S_RegisterSound( va( "sound/player/announce/%s_wins.wav", skinname), qfalse );
			}
		}
	}	

	//APSFIXME - Degenerate no models case

	s_playermodel.numpages = s_playermodel.nummodels/MAX_MODELSPERPAGE;
	if (s_playermodel.nummodels % MAX_MODELSPERPAGE)
		s_playermodel.numpages++;
}