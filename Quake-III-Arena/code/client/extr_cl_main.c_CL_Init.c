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
struct TYPE_2__ {scalar_t__ realtime; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_DISCONNECTED ; 
 int /*<<< orphan*/  CL_ClearState () ; 
 int /*<<< orphan*/  CL_Clientinfo_f ; 
 int /*<<< orphan*/  CL_Configstrings_f ; 
 int /*<<< orphan*/  CL_Connect_f ; 
 int /*<<< orphan*/  CL_Disconnect_f ; 
 int /*<<< orphan*/  CL_ForwardToServer_f ; 
 int /*<<< orphan*/  CL_GlobalServers_f ; 
 int /*<<< orphan*/  CL_InitInput () ; 
 int /*<<< orphan*/  CL_InitRef () ; 
 int /*<<< orphan*/  CL_LocalServers_f ; 
 int /*<<< orphan*/  CL_OpenedPK3List_f ; 
 int /*<<< orphan*/  CL_Ping_f ; 
 int /*<<< orphan*/  CL_PlayCinematic_f ; 
 int /*<<< orphan*/  CL_PlayDemo_f ; 
 int /*<<< orphan*/  CL_Rcon_f ; 
 int /*<<< orphan*/  CL_Reconnect_f ; 
 int /*<<< orphan*/  CL_Record_f ; 
 int /*<<< orphan*/  CL_ReferencedPK3List_f ; 
 int /*<<< orphan*/  CL_ServerStatus_f ; 
 int /*<<< orphan*/  CL_SetModel_f ; 
 int /*<<< orphan*/  CL_Setenv_f ; 
 int /*<<< orphan*/  CL_ShowIP_f ; 
 int /*<<< orphan*/  CL_Snd_Restart_f ; 
 int /*<<< orphan*/  CL_StopRecord_f ; 
 int /*<<< orphan*/  CL_Vid_Restart_f ; 
 int CVAR_ARCHIVE ; 
 int CVAR_ROM ; 
 int CVAR_SERVERINFO ; 
 int CVAR_TEMP ; 
 int CVAR_USERINFO ; 
 int /*<<< orphan*/  Cbuf_Execute () ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Con_Init () ; 
 void* Cvar_Get (char*,char*,int) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  SCR_Init () ; 
 void* cl_activeAction ; 
 void* cl_allowDownload ; 
 void* cl_anglespeedkey ; 
 void* cl_avidemo ; 
 void* cl_conXOffset ; 
 void* cl_forceavidemo ; 
 void* cl_freelook ; 
 void* cl_freezeDemo ; 
 void* cl_inGameVideo ; 
 void* cl_maxpackets ; 
 void* cl_motd ; 
 void* cl_motdString ; 
 void* cl_mouseAccel ; 
 void* cl_noprint ; 
 void* cl_packetdup ; 
 void* cl_pitchspeed ; 
 void* cl_run ; 
 void* cl_sensitivity ; 
 void* cl_serverStatusResendTime ; 
 void* cl_showMouseRate ; 
 void* cl_showSend ; 
 void* cl_showTimeDelta ; 
 void* cl_shownet ; 
 void* cl_timeNudge ; 
 void* cl_timedemo ; 
 void* cl_timeout ; 
 void* cl_yawspeed ; 
 TYPE_1__ cls ; 
 void* m_filter ; 
 void* m_forward ; 
 void* m_pitch ; 
 void* m_side ; 
 void* m_yaw ; 
 void* rconAddress ; 
 void* rcon_client_password ; 

void CL_Init( void ) {
	Com_Printf( "----- Client Initialization -----\n" );

	Con_Init ();	

	CL_ClearState ();

	cls.state = CA_DISCONNECTED;	// no longer CA_UNINITIALIZED

	cls.realtime = 0;

	CL_InitInput ();

	//
	// register our variables
	//
	cl_noprint = Cvar_Get( "cl_noprint", "0", 0 );
	cl_motd = Cvar_Get ("cl_motd", "1", 0);

	cl_timeout = Cvar_Get ("cl_timeout", "200", 0);

	cl_timeNudge = Cvar_Get ("cl_timeNudge", "0", CVAR_TEMP );
	cl_shownet = Cvar_Get ("cl_shownet", "0", CVAR_TEMP );
	cl_showSend = Cvar_Get ("cl_showSend", "0", CVAR_TEMP );
	cl_showTimeDelta = Cvar_Get ("cl_showTimeDelta", "0", CVAR_TEMP );
	cl_freezeDemo = Cvar_Get ("cl_freezeDemo", "0", CVAR_TEMP );
	rcon_client_password = Cvar_Get ("rconPassword", "", CVAR_TEMP );
	cl_activeAction = Cvar_Get( "activeAction", "", CVAR_TEMP );

	cl_timedemo = Cvar_Get ("timedemo", "0", 0);
	cl_avidemo = Cvar_Get ("cl_avidemo", "0", 0);
	cl_forceavidemo = Cvar_Get ("cl_forceavidemo", "0", 0);

	rconAddress = Cvar_Get ("rconAddress", "", 0);

	cl_yawspeed = Cvar_Get ("cl_yawspeed", "140", CVAR_ARCHIVE);
	cl_pitchspeed = Cvar_Get ("cl_pitchspeed", "140", CVAR_ARCHIVE);
	cl_anglespeedkey = Cvar_Get ("cl_anglespeedkey", "1.5", 0);

	cl_maxpackets = Cvar_Get ("cl_maxpackets", "30", CVAR_ARCHIVE );
	cl_packetdup = Cvar_Get ("cl_packetdup", "1", CVAR_ARCHIVE );

	cl_run = Cvar_Get ("cl_run", "1", CVAR_ARCHIVE);
	cl_sensitivity = Cvar_Get ("sensitivity", "5", CVAR_ARCHIVE);
	cl_mouseAccel = Cvar_Get ("cl_mouseAccel", "0", CVAR_ARCHIVE);
	cl_freelook = Cvar_Get( "cl_freelook", "1", CVAR_ARCHIVE );

	cl_showMouseRate = Cvar_Get ("cl_showmouserate", "0", 0);

	cl_allowDownload = Cvar_Get ("cl_allowDownload", "0", CVAR_ARCHIVE);

	cl_conXOffset = Cvar_Get ("cl_conXOffset", "0", 0);
#ifdef MACOS_X
        // In game video is REALLY slow in Mac OS X right now due to driver slowness
	cl_inGameVideo = Cvar_Get ("r_inGameVideo", "0", CVAR_ARCHIVE);
#else
	cl_inGameVideo = Cvar_Get ("r_inGameVideo", "1", CVAR_ARCHIVE);
#endif

	cl_serverStatusResendTime = Cvar_Get ("cl_serverStatusResendTime", "750", 0);

	// init autoswitch so the ui will have it correctly even
	// if the cgame hasn't been started
	Cvar_Get ("cg_autoswitch", "1", CVAR_ARCHIVE);

	m_pitch = Cvar_Get ("m_pitch", "0.022", CVAR_ARCHIVE);
	m_yaw = Cvar_Get ("m_yaw", "0.022", CVAR_ARCHIVE);
	m_forward = Cvar_Get ("m_forward", "0.25", CVAR_ARCHIVE);
	m_side = Cvar_Get ("m_side", "0.25", CVAR_ARCHIVE);
#ifdef MACOS_X
        // Input is jittery on OS X w/o this
	m_filter = Cvar_Get ("m_filter", "1", CVAR_ARCHIVE);
#else
	m_filter = Cvar_Get ("m_filter", "0", CVAR_ARCHIVE);
#endif

	cl_motdString = Cvar_Get( "cl_motdString", "", CVAR_ROM );

	Cvar_Get( "cl_maxPing", "800", CVAR_ARCHIVE );


	// userinfo
	Cvar_Get ("name", "UnnamedPlayer", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("rate", "3000", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("snaps", "20", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("model", "sarge", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("headmodel", "sarge", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("team_model", "james", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("team_headmodel", "*james", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("g_redTeam", "Stroggs", CVAR_SERVERINFO | CVAR_ARCHIVE);
	Cvar_Get ("g_blueTeam", "Pagans", CVAR_SERVERINFO | CVAR_ARCHIVE);
	Cvar_Get ("color1",  "4", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("color2", "5", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("handicap", "100", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("teamtask", "0", CVAR_USERINFO );
	Cvar_Get ("sex", "male", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("cl_anonymous", "0", CVAR_USERINFO | CVAR_ARCHIVE );

	Cvar_Get ("password", "", CVAR_USERINFO);
	Cvar_Get ("cg_predictItems", "1", CVAR_USERINFO | CVAR_ARCHIVE );


	// cgame might not be initialized before menu is used
	Cvar_Get ("cg_viewsize", "100", CVAR_ARCHIVE );

	//
	// register our commands
	//
	Cmd_AddCommand ("cmd", CL_ForwardToServer_f);
	Cmd_AddCommand ("configstrings", CL_Configstrings_f);
	Cmd_AddCommand ("clientinfo", CL_Clientinfo_f);
	Cmd_AddCommand ("snd_restart", CL_Snd_Restart_f);
	Cmd_AddCommand ("vid_restart", CL_Vid_Restart_f);
	Cmd_AddCommand ("disconnect", CL_Disconnect_f);
	Cmd_AddCommand ("record", CL_Record_f);
	Cmd_AddCommand ("demo", CL_PlayDemo_f);
	Cmd_AddCommand ("cinematic", CL_PlayCinematic_f);
	Cmd_AddCommand ("stoprecord", CL_StopRecord_f);
	Cmd_AddCommand ("connect", CL_Connect_f);
	Cmd_AddCommand ("reconnect", CL_Reconnect_f);
	Cmd_AddCommand ("localservers", CL_LocalServers_f);
	Cmd_AddCommand ("globalservers", CL_GlobalServers_f);
	Cmd_AddCommand ("rcon", CL_Rcon_f);
	Cmd_AddCommand ("setenv", CL_Setenv_f );
	Cmd_AddCommand ("ping", CL_Ping_f );
	Cmd_AddCommand ("serverstatus", CL_ServerStatus_f );
	Cmd_AddCommand ("showip", CL_ShowIP_f );
	Cmd_AddCommand ("fs_openedList", CL_OpenedPK3List_f );
	Cmd_AddCommand ("fs_referencedList", CL_ReferencedPK3List_f );
	Cmd_AddCommand ("model", CL_SetModel_f );
	CL_InitRef();

	SCR_Init ();

	Cbuf_Execute ();

	Cvar_Set( "cl_running", "1" );

	Com_Printf( "----- Client Initialization Complete -----\n" );
}