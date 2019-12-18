#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int time_t ;
struct tm {int tm_hour; int tm_min; int tm_sec; int tm_mday; } ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_13__ {TYPE_1__ allocation; } ;
struct TYPE_12__ {char* Name; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* Resize ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int cdcoretype; int regionid; int carttype; int sh2coretype; int m68kcoretype; int vidcoretype; int osdcoretype; int sndcoretype; int percoretype; int clocksync; long basetime; int usethreads; int videoformattype; int /*<<< orphan*/ * mpegpath; int /*<<< orphan*/ * buppath; int /*<<< orphan*/ * cartpath; int /*<<< orphan*/ * cdpath; int /*<<< orphan*/ * biospath; } ;
struct TYPE_9__ {int state; int /*<<< orphan*/  area; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cs2ChangeCDCore (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_7__* GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_KEY_FILE_NONE ; 
 int /*<<< orphan*/  OSDChangeCore (int) ; 
 TYPE_6__* PERCore ; 
#define  PERMOUSE 129 
#define  PERPAD 128 
 int /*<<< orphan*/  PORTDATA1 ; 
 int /*<<< orphan*/  PerInit (int) ; 
 int /*<<< orphan*/  PerMouseAdd (int /*<<< orphan*/ *) ; 
 char** PerMouseNames ; 
 int /*<<< orphan*/  PerPadAdd (int /*<<< orphan*/ *) ; 
 char** PerPadNames ; 
 int /*<<< orphan*/  PerPortReset () ; 
 int /*<<< orphan*/  PerSetKey (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScspChangeSoundCore (int) ; 
 int /*<<< orphan*/  ScspSetFrameAccurate (int) ; 
 int /*<<< orphan*/  ScspSetVolume (int) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__* VIDCore ; 
 int /*<<< orphan*/  VIDSoftSetBilinear (int) ; 
 int /*<<< orphan*/  VideoChangeCore (int) ; 
 int YUI_IS_INIT ; 
 TYPE_2__* YUI_WINDOW (int /*<<< orphan*/ ) ; 
 void* biospath ; 
 void* buppath ; 
 void* cartpath ; 
 void* cdpath ; 
 void* g_key_file_get_boolean (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int g_key_file_get_integer (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 void* g_key_file_get_value (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_load_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strlcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  inifile ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  localtime_r (int*,struct tm*) ; 
 void* mpegpath ; 
 int /*<<< orphan*/  padbits ; 
 scalar_t__ safe_strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ yinit ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_resize (int,int,int) ; 
 int /*<<< orphan*/  yui_window_set_frameskip (TYPE_2__*,int) ; 

__attribute__((used)) static gboolean yui_settings_load(void) {
	int i, tmp;
	long tmptime;
	gchar * stmp;
	gboolean mustRestart = FALSE;

	g_key_file_load_from_file(keyfile, inifile, G_KEY_FILE_NONE, 0);

	/* bios */
	stmp = g_key_file_get_value(keyfile, "General", "BiosPath", 0);
	if (stmp && !*stmp) stmp = NULL;
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && safe_strcmp(stmp, yinit.biospath)) {
		mustRestart = TRUE;
	}
	if (stmp) {
		g_strlcpy(biospath, stmp, 256);
		yinit.biospath = biospath;
	}
	else yinit.biospath = NULL;

	/* cd core */
	stmp = g_key_file_get_value(keyfile, "General", "CDROMDrive", 0);
	if (stmp && !*stmp) stmp = NULL;
	if((YUI_WINDOW(yui)->state & YUI_IS_INIT) && safe_strcmp(stmp, yinit.cdpath)) {
		Cs2ChangeCDCore(yinit.cdcoretype, stmp);
	}
	if (stmp) g_strlcpy(cdpath, stmp, 256);

	tmp = yinit.cdcoretype;
	yinit.cdcoretype = g_key_file_get_integer(keyfile, "General", "CDROMCore", 0);
	if((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.cdcoretype)) {
		Cs2ChangeCDCore(yinit.cdcoretype, yinit.cdpath);
	}

	/* region */
	{
		char * region = g_key_file_get_value(keyfile, "General", "Region", 0);
		tmp = yinit.regionid;
		if ((region == 0) || !strcmp(region, "Auto")) {
			yinit.regionid = 0;
		} else {
			switch(region[0]) {
				case 'J': yinit.regionid = 1; break;
				case 'T': yinit.regionid = 2; break;
				case 'U': yinit.regionid = 4; break;
				case 'B': yinit.regionid = 5; break;
				case 'K': yinit.regionid = 6; break;
				case 'A': yinit.regionid = 0xA; break;
				case 'E': yinit.regionid = 0xC; break;
				case 'L': yinit.regionid = 0xD; break;
			}
		}

		if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.regionid)) {
			mustRestart = TRUE;
		}
	}

	/* cart */
	stmp = g_key_file_get_value(keyfile, "General", "CartPath", 0);
	if (stmp && !*stmp) stmp = NULL;
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && safe_strcmp(stmp, yinit.cartpath)) {
		mustRestart = TRUE;
	}
	if (stmp) {
		g_strlcpy(cartpath, stmp, 256);
		yinit.cartpath = cartpath;
	}
	else yinit.cartpath = NULL;

	tmp = yinit.carttype;
	yinit.carttype = g_key_file_get_integer(keyfile, "General", "CartType", 0);
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.carttype)) {
          mustRestart = TRUE;
	}

	/* backup ram */
	stmp = g_key_file_get_value(keyfile, "General", "BackupRamPath", 0);
	if (stmp && !*stmp) stmp = NULL;
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && safe_strcmp(stmp, yinit.buppath)) {
		mustRestart = TRUE;
	}
	if (stmp) {
		g_strlcpy(buppath, stmp, 256);
		yinit.buppath = buppath;
	}
	else yinit.buppath = NULL;

	/* mpeg rom */
	stmp = g_key_file_get_value(keyfile, "General", "MpegRomPath", 0);
	if (stmp && !*stmp) stmp = NULL;
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && safe_strcmp(stmp, yinit.mpegpath)) {
		mustRestart = TRUE;
	}
	if (stmp) {
		g_strlcpy(mpegpath, stmp, 256);
		yinit.mpegpath = mpegpath;
	}
	else yinit.mpegpath = NULL;

	/* sh2 */
	tmp = yinit.sh2coretype;
	yinit.sh2coretype = g_key_file_get_integer(keyfile, "General", "SH2Int", 0);
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.sh2coretype)) {
		mustRestart = TRUE;
	}

	/* m68k */
	tmp = yinit.m68kcoretype;
	yinit.m68kcoretype = g_key_file_get_integer(keyfile, "General", "M68kInt", 0);
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.m68kcoretype)) {
		mustRestart = TRUE;
	}

	/* video core */
	tmp = yinit.vidcoretype;
	yinit.vidcoretype = g_key_file_get_integer(keyfile, "General", "VideoCore", 0);
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.vidcoretype)) {
		VideoChangeCore(yinit.vidcoretype);
		VIDCore->Resize(
			GTK_WIDGET(YUI_WINDOW(yui)->area)->allocation.width,
			GTK_WIDGET(YUI_WINDOW(yui)->area)->allocation.height,
			FALSE);
	}

	/* osd core */
	tmp = yinit.osdcoretype;
	yinit.osdcoretype = g_key_file_get_integer(keyfile, "General", "OSDCore", 0);
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.osdcoretype)) {
		OSDChangeCore(yinit.osdcoretype);
	}

	/* sound core */
	tmp = yinit.sndcoretype;
	yinit.sndcoretype = g_key_file_get_integer(keyfile, "General", "SoundCore", 0);
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.sndcoretype)) {
		ScspChangeSoundCore(yinit.sndcoretype);
	}

	ScspSetVolume(g_key_file_get_integer(keyfile, "General", "Volume", NULL));

	/* peripheral core */
	yinit.percoretype = g_key_file_get_integer(keyfile, "General", "PerCore", 0);

	/* audio sync */
	tmp = g_key_file_get_boolean(keyfile, "General", "AudioSync", 0);
	ScspSetFrameAccurate(tmp);

	/* clock sync */
	tmp = yinit.clocksync;
	yinit.clocksync = g_key_file_get_boolean(keyfile, "General", "ClockSync", 0);
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.clocksync)) {
		mustRestart = TRUE;
	}
	tmptime = yinit.basetime;
	tmp = g_key_file_get_boolean(keyfile, "General", "FixedBaseTime", 0);
	if (tmp && yinit.clocksync) {
		/* Find timestamp of 1998-01-01 12:00 in the local time zone */
		time_t utc = 883656000;  // 1998-01-01 12:00 UTC
		struct tm tm;
		long local, noon;
		localtime_r(&utc, &tm);
		local = tm.tm_hour*3600 + tm.tm_min*60 + tm.tm_sec;
		if (tm.tm_mday == 2)  // 1998-01-02
			local += 86400;
		else if (tm.tm_mday == 31)  // 1997-12-31
			local -= 86400;
		noon = 12*3600 + 0*60 + 0;
		yinit.basetime = (long)utc + (noon - local);
	} else {
		yinit.basetime = 0;
	}
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmptime != yinit.basetime)) {
		mustRestart = TRUE;
	}

	/* threads */
	tmp = g_key_file_get_boolean(keyfile, "General", "UseThreads", 0);
	if ((YUI_WINDOW(yui)->state & YUI_IS_INIT) && (tmp != yinit.usethreads)) {
		mustRestart = TRUE;
	}
	yinit.usethreads = tmp;

	PerInit(yinit.percoretype);

	PerPortReset();
	switch(g_key_file_get_integer(keyfile, "General", "PerType", NULL))
	{
		case PERMOUSE:
			padbits = PerMouseAdd(&PORTDATA1);
			i = 0;

			while(PerMouseNames[i]) {
				char tmp[100];
				u32 key;
				sprintf(tmp, "Mouse.%s.1", PerMouseNames[i]);
	  			key = g_key_file_get_integer(keyfile, PERCore->Name, tmp, 0);
		  		PerSetKey(key, i + 13, padbits);
		  		i++;
			}
			break;
		case PERPAD:
		default:
			padbits = PerPadAdd(&PORTDATA1);
			i = 0;

			while(PerPadNames[i]) {
				char tmp[100];
				u32 key;
				sprintf(tmp, "Pad.%s.1", PerPadNames[i]);
	  			key = g_key_file_get_integer(keyfile, PERCore->Name, tmp, 0);
		  		PerSetKey(key, i, padbits);
		  		i++;
			}
	}

	yui_resize(g_key_file_get_integer(keyfile, "General", "Width", 0),
			g_key_file_get_integer(keyfile, "General", "Height", 0),
			g_key_file_get_integer(keyfile, "General", "Fullscreen", 0));

        yinit.videoformattype = g_key_file_get_integer(keyfile, "General", "VideoFormat", 0);

	yui_window_set_frameskip(YUI_WINDOW(yui), g_key_file_get_integer(keyfile, "General", "Frameskip", NULL));
	
	VIDSoftSetBilinear(g_key_file_get_integer(keyfile, "General", "Bilinear", 0));

	return mustRestart;
}