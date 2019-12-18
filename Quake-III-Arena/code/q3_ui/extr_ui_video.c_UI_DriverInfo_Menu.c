#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  driverinfo_t ;
struct TYPE_9__ {int x; int y; int flags; int /*<<< orphan*/  id; int /*<<< orphan*/  callback; int /*<<< orphan*/  name; void* type; } ;
struct TYPE_14__ {char* string; int width; int height; int /*<<< orphan*/  focuspic; TYPE_1__ generic; int /*<<< orphan*/  style; int /*<<< orphan*/  color; } ;
struct TYPE_13__ {int /*<<< orphan*/  draw; int /*<<< orphan*/  fullscreen; } ;
struct TYPE_12__ {char* stringbuff; int numstrings; char** strings; TYPE_6__ menu; TYPE_8__ back; TYPE_8__ framer; TYPE_8__ framel; TYPE_8__ banner; } ;
struct TYPE_10__ {int /*<<< orphan*/  extensions_string; } ;
struct TYPE_11__ {TYPE_2__ glconfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVERINFO_BACK0 ; 
 int /*<<< orphan*/  DRIVERINFO_BACK1 ; 
 int /*<<< orphan*/  DRIVERINFO_FRAMEL ; 
 int /*<<< orphan*/  DRIVERINFO_FRAMER ; 
 int /*<<< orphan*/  DriverInfo_Cache () ; 
 int /*<<< orphan*/  DriverInfo_Event ; 
 int /*<<< orphan*/  DriverInfo_MenuDraw ; 
 int /*<<< orphan*/  ID_DRIVERINFOBACK ; 
 void* MTYPE_BITMAP ; 
 void* MTYPE_BTEXT ; 
 int /*<<< orphan*/  Menu_AddItem (TYPE_6__*,TYPE_8__*) ; 
 void* QMF_INACTIVE ; 
 int QMF_LEFT_JUSTIFY ; 
 int QMF_PULSEIFFOCUS ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_CENTER ; 
 int /*<<< orphan*/  UI_PushMenu (TYPE_6__*) ; 
 int /*<<< orphan*/  color_white ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_4__ s_driverinfo ; 
 int strlen (char*) ; 
 TYPE_3__ uis ; 

__attribute__((used)) static void UI_DriverInfo_Menu( void )
{
	char*	eptr;
	int		i;
	int		len;

	// zero set all our globals
	memset( &s_driverinfo, 0 ,sizeof(driverinfo_t) );

	DriverInfo_Cache();

	s_driverinfo.menu.fullscreen = qtrue;
	s_driverinfo.menu.draw       = DriverInfo_MenuDraw;

	s_driverinfo.banner.generic.type  = MTYPE_BTEXT;
	s_driverinfo.banner.generic.x	  = 320;
	s_driverinfo.banner.generic.y	  = 16;
	s_driverinfo.banner.string		  = "DRIVER INFO";
	s_driverinfo.banner.color	      = color_white;
	s_driverinfo.banner.style	      = UI_CENTER;

	s_driverinfo.framel.generic.type  = MTYPE_BITMAP;
	s_driverinfo.framel.generic.name  = DRIVERINFO_FRAMEL;
	s_driverinfo.framel.generic.flags = QMF_INACTIVE;
	s_driverinfo.framel.generic.x	  = 0;
	s_driverinfo.framel.generic.y	  = 78;
	s_driverinfo.framel.width  	      = 256;
	s_driverinfo.framel.height  	  = 329;

	s_driverinfo.framer.generic.type  = MTYPE_BITMAP;
	s_driverinfo.framer.generic.name  = DRIVERINFO_FRAMER;
	s_driverinfo.framer.generic.flags = QMF_INACTIVE;
	s_driverinfo.framer.generic.x	  = 376;
	s_driverinfo.framer.generic.y	  = 76;
	s_driverinfo.framer.width  	      = 256;
	s_driverinfo.framer.height  	  = 334;

	s_driverinfo.back.generic.type	   = MTYPE_BITMAP;
	s_driverinfo.back.generic.name     = DRIVERINFO_BACK0;
	s_driverinfo.back.generic.flags    = QMF_LEFT_JUSTIFY|QMF_PULSEIFFOCUS;
	s_driverinfo.back.generic.callback = DriverInfo_Event;
	s_driverinfo.back.generic.id	   = ID_DRIVERINFOBACK;
	s_driverinfo.back.generic.x		   = 0;
	s_driverinfo.back.generic.y		   = 480-64;
	s_driverinfo.back.width  		   = 128;
	s_driverinfo.back.height  		   = 64;
	s_driverinfo.back.focuspic         = DRIVERINFO_BACK1;

  // TTimo: overflow with particularly long GL extensions (such as the gf3)
  // https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=399
  // NOTE: could have pushed the size of stringbuff, but the list is already out of the screen
  // (no matter what your resolution)
  Q_strncpyz(s_driverinfo.stringbuff, uis.glconfig.extensions_string, 1024);

	// build null terminated extension strings
	eptr = s_driverinfo.stringbuff;
	while ( s_driverinfo.numstrings<40 && *eptr )
	{
		while ( *eptr && *eptr == ' ' )
			*eptr++ = '\0';

		// track start of valid string
		if (*eptr && *eptr != ' ')
			s_driverinfo.strings[s_driverinfo.numstrings++] = eptr;

		while ( *eptr && *eptr != ' ' )
			eptr++;
	}

	// safety length strings for display
	for (i=0; i<s_driverinfo.numstrings; i++) {
		len = strlen(s_driverinfo.strings[i]);
		if (len > 32) {
			s_driverinfo.strings[i][len-1] = '>';
			s_driverinfo.strings[i][len]   = '\0';
		}
	}

	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.banner );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.framel );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.framer );
	Menu_AddItem( &s_driverinfo.menu, &s_driverinfo.back );

	UI_PushMenu( &s_driverinfo.menu );
}