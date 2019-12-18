#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int id; } ;
typedef  TYPE_11__ menucommon_s ;
struct TYPE_27__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_26__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_25__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_24__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_23__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_22__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_21__ {int curvalue; } ;
struct TYPE_20__ {size_t curvalue; } ;
struct TYPE_19__ {int curvalue; } ;
struct TYPE_15__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_18__ {TYPE_10__ fs; TYPE_9__ filter; TYPE_8__ geometry; TYPE_7__ texturebits; TYPE_6__ colordepth; TYPE_5__ lighting; TYPE_4__ tq; TYPE_3__ mode; TYPE_2__ list; TYPE_1__ driver; } ;
struct TYPE_17__ {int mode; int /*<<< orphan*/  fullscreen; int /*<<< orphan*/  filter; int /*<<< orphan*/  geometry; int /*<<< orphan*/  texturebits; int /*<<< orphan*/  colordepth; int /*<<< orphan*/  lighting; int /*<<< orphan*/  tq; } ;
typedef  TYPE_12__ InitialVideoOptions_s ;

/* Variables and functions */
#define  ID_BACK2 135 
#define  ID_DISPLAY 134 
#define  ID_DRIVERINFO 133 
#define  ID_GRAPHICS 132 
#define  ID_LIST 131 
#define  ID_MODE 130 
#define  ID_NETWORK 129 
#define  ID_SOUND 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_DisplayOptionsMenu () ; 
 int /*<<< orphan*/  UI_DriverInfo_Menu () ; 
 int /*<<< orphan*/  UI_NetworkOptionsMenu () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_SoundOptionsMenu () ; 
 TYPE_14__ s_graphicsoptions ; 
 TYPE_12__* s_ivo_templates ; 

__attribute__((used)) static void GraphicsOptions_Event( void* ptr, int event ) {
	InitialVideoOptions_s *ivo;

	if( event != QM_ACTIVATED ) {
	 	return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_MODE:
		// clamp 3dfx video modes
		if ( s_graphicsoptions.driver.curvalue == 1 )
		{
			if ( s_graphicsoptions.mode.curvalue < 2 )
				s_graphicsoptions.mode.curvalue = 2;
			else if ( s_graphicsoptions.mode.curvalue > 6 )
				s_graphicsoptions.mode.curvalue = 6;
		}
		break;

	case ID_LIST:
		ivo = &s_ivo_templates[s_graphicsoptions.list.curvalue];

		s_graphicsoptions.mode.curvalue        = ivo->mode;
		s_graphicsoptions.tq.curvalue          = ivo->tq;
		s_graphicsoptions.lighting.curvalue    = ivo->lighting;
		s_graphicsoptions.colordepth.curvalue  = ivo->colordepth;
		s_graphicsoptions.texturebits.curvalue = ivo->texturebits;
		s_graphicsoptions.geometry.curvalue    = ivo->geometry;
		s_graphicsoptions.filter.curvalue      = ivo->filter;
		s_graphicsoptions.fs.curvalue          = ivo->fullscreen;
		break;

	case ID_DRIVERINFO:
		UI_DriverInfo_Menu();
		break;

	case ID_BACK2:
		UI_PopMenu();
		break;

	case ID_GRAPHICS:
		break;

	case ID_DISPLAY:
		UI_PopMenu();
		UI_DisplayOptionsMenu();
		break;

	case ID_SOUND:
		UI_PopMenu();
		UI_SoundOptionsMenu();
		break;

	case ID_NETWORK:
		UI_PopMenu();
		UI_NetworkOptionsMenu();
		break;
	}
}