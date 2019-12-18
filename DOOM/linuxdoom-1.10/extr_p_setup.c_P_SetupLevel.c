#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  skill_t ;
struct TYPE_4__ {int viewz; int /*<<< orphan*/ * mo; scalar_t__ itemcount; scalar_t__ secretcount; scalar_t__ killcount; } ;
struct TYPE_3__ {int partime; scalar_t__ maxfrags; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_DeathMatchSpawnPlayer (int) ; 
 scalar_t__ MAXINT ; 
 int MAXPLAYERS ; 
 scalar_t__ ML_BLOCKMAP ; 
 scalar_t__ ML_LINEDEFS ; 
 scalar_t__ ML_NODES ; 
 scalar_t__ ML_REJECT ; 
 scalar_t__ ML_SECTORS ; 
 scalar_t__ ML_SEGS ; 
 scalar_t__ ML_SIDEDEFS ; 
 scalar_t__ ML_SSECTORS ; 
 scalar_t__ ML_THINGS ; 
 scalar_t__ ML_VERTEXES ; 
 int /*<<< orphan*/  PU_LEVEL ; 
 scalar_t__ PU_PURGELEVEL ; 
 int /*<<< orphan*/  P_GroupLines () ; 
 int /*<<< orphan*/  P_InitThinkers () ; 
 int /*<<< orphan*/  P_LoadBlockMap (scalar_t__) ; 
 int /*<<< orphan*/  P_LoadLineDefs (scalar_t__) ; 
 int /*<<< orphan*/  P_LoadNodes (scalar_t__) ; 
 int /*<<< orphan*/  P_LoadSectors (scalar_t__) ; 
 int /*<<< orphan*/  P_LoadSegs (scalar_t__) ; 
 int /*<<< orphan*/  P_LoadSideDefs (scalar_t__) ; 
 int /*<<< orphan*/  P_LoadSubsectors (scalar_t__) ; 
 int /*<<< orphan*/  P_LoadThings (scalar_t__) ; 
 int /*<<< orphan*/  P_LoadVertexes (scalar_t__) ; 
 int /*<<< orphan*/  P_SpawnSpecials () ; 
 int /*<<< orphan*/  R_PrecacheLevel () ; 
 int /*<<< orphan*/  S_Start () ; 
 int /*<<< orphan*/  W_CacheLumpNum (scalar_t__,int /*<<< orphan*/ ) ; 
 int W_GetNumForName (char*) ; 
 int /*<<< orphan*/  W_Reload () ; 
 int /*<<< orphan*/  Z_FileDumpHeap (scalar_t__) ; 
 int /*<<< orphan*/  Z_FreeTags (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bodyqueslot ; 
 scalar_t__ commercial ; 
 size_t consoleplayer ; 
 scalar_t__ deathmatch ; 
 int /*<<< orphan*/  deathmatch_p ; 
 int /*<<< orphan*/  deathmatchstarts ; 
 scalar_t__ debugfile ; 
 scalar_t__ gamemode ; 
 scalar_t__ iquehead ; 
 scalar_t__ iquetail ; 
 scalar_t__ leveltime ; 
 scalar_t__* playeringame ; 
 TYPE_2__* players ; 
 scalar_t__ precache ; 
 int /*<<< orphan*/  rejectmatrix ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ totalitems ; 
 scalar_t__ totalkills ; 
 scalar_t__ totalsecret ; 
 TYPE_1__ wminfo ; 

void
P_SetupLevel
( int		episode,
  int		map,
  int		playermask,
  skill_t	skill)
{
    int		i;
    char	lumpname[9];
    int		lumpnum;
	
    totalkills = totalitems = totalsecret = wminfo.maxfrags = 0;
    wminfo.partime = 180;
    for (i=0 ; i<MAXPLAYERS ; i++)
    {
	players[i].killcount = players[i].secretcount 
	    = players[i].itemcount = 0;
    }

    // Initial height of PointOfView
    // will be set by player think.
    players[consoleplayer].viewz = 1; 

    // Make sure all sounds are stopped before Z_FreeTags.
    S_Start ();			

    
#if 0 // UNUSED
    if (debugfile)
    {
	Z_FreeTags (PU_LEVEL, MAXINT);
	Z_FileDumpHeap (debugfile);
    }
    else
#endif
	Z_FreeTags (PU_LEVEL, PU_PURGELEVEL-1);


    // UNUSED W_Profile ();
    P_InitThinkers ();

    // if working with a devlopment map, reload it
    W_Reload ();			
	   
    // find map name
    if ( gamemode == commercial)
    {
	if (map<10)
	    sprintf (lumpname,"map0%i", map);
	else
	    sprintf (lumpname,"map%i", map);
    }
    else
    {
	lumpname[0] = 'E';
	lumpname[1] = '0' + episode;
	lumpname[2] = 'M';
	lumpname[3] = '0' + map;
	lumpname[4] = 0;
    }

    lumpnum = W_GetNumForName (lumpname);
	
    leveltime = 0;
	
    // note: most of this ordering is important	
    P_LoadBlockMap (lumpnum+ML_BLOCKMAP);
    P_LoadVertexes (lumpnum+ML_VERTEXES);
    P_LoadSectors (lumpnum+ML_SECTORS);
    P_LoadSideDefs (lumpnum+ML_SIDEDEFS);

    P_LoadLineDefs (lumpnum+ML_LINEDEFS);
    P_LoadSubsectors (lumpnum+ML_SSECTORS);
    P_LoadNodes (lumpnum+ML_NODES);
    P_LoadSegs (lumpnum+ML_SEGS);
	
    rejectmatrix = W_CacheLumpNum (lumpnum+ML_REJECT,PU_LEVEL);
    P_GroupLines ();

    bodyqueslot = 0;
    deathmatch_p = deathmatchstarts;
    P_LoadThings (lumpnum+ML_THINGS);
    
    // if deathmatch, randomly spawn the active players
    if (deathmatch)
    {
	for (i=0 ; i<MAXPLAYERS ; i++)
	    if (playeringame[i])
	    {
		players[i].mo = NULL;
		G_DeathMatchSpawnPlayer (i);
	    }
			
    }

    // clear special respawning que
    iquehead = iquetail = 0;		
	
    // set up world state
    P_SpawnSpecials ();
	
    // build subsector connect matrix
    //	UNUSED P_ConnectSubsectors ();

    // preload graphics
    if (precache)
	R_PrecacheLevel ();

    //printf ("free memory: 0x%x\n", Z_FreeMemory());

}