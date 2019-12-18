#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_3__ ;
typedef  struct TYPE_51__   TYPE_2__ ;
typedef  struct TYPE_50__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_50__ {float x; float y; float w; float h; } ;
typedef  TYPE_1__ rectDef_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_52__ {int /*<<< orphan*/  integer; } ;
struct TYPE_51__ {scalar_t__ integer; } ;

/* Variables and functions */
#define  CG_1STPLACE 186 
#define  CG_2NDPLACE 185 
#define  CG_ACCURACY 184 
#define  CG_AREA_CHAT 183 
#define  CG_AREA_POWERUP 182 
#define  CG_AREA_SYSTEMCHAT 181 
#define  CG_AREA_TEAMCHAT 180 
#define  CG_ASSISTS 179 
#define  CG_BLUE_FLAGHEAD 178 
#define  CG_BLUE_FLAGNAME 177 
#define  CG_BLUE_FLAGSTATUS 176 
#define  CG_BLUE_NAME 175 
#define  CG_BLUE_SCORE 174 
#define  CG_CAPFRAGLIMIT 173 
#define  CG_CAPTURES 172 
#define  CG_CTF_POWERUP 171 
#define  CG_DEFEND 170 
 int /*<<< orphan*/  CG_Draw1stPlace (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_Draw2ndPlace (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawAreaChat (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawAreaPowerUp (TYPE_1__*,int,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawAreaSystemChat (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawAreaTeamChat (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawBlueFlagHead (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_DrawBlueFlagName (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawBlueFlagStatus (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawBlueName (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawBlueScore (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawCTFPowerUp (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_DrawCapFragLimit (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawGameStatus (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawGameType (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawKiller (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawMedal (int,TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawNewTeamInfo (TYPE_1__*,float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawPlayerAmmoIcon (TYPE_1__*,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerAmmoValue (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerArmorIcon (TYPE_1__*,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerArmorValue (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerHasFlag (TYPE_1__*,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerHead (TYPE_1__*,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerHealth (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerItem (TYPE_1__*,float,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerLocation (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerScore (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawPlayerStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_DrawRedFlagHead (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_DrawRedFlagName (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawRedFlagStatus (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawRedName (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawRedScore (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawSelectedPlayerArmor (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawSelectedPlayerHead (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  CG_DrawSelectedPlayerHealth (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawSelectedPlayerLocation (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_DrawSelectedPlayerName (TYPE_1__*,float,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CG_DrawSelectedPlayerPowerup (TYPE_1__*,int) ; 
 int /*<<< orphan*/  CG_DrawSelectedPlayerStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_DrawSelectedPlayerWeapon (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_DrawTeamColor (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawTeamSpectators (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  CG_EXCELLENT 169 
#define  CG_GAME_STATUS 168 
#define  CG_GAME_TYPE 167 
#define  CG_GAUNTLET 166 
#define  CG_HARVESTER_SKULLS 165 
#define  CG_HARVESTER_SKULLS2D 164 
 int /*<<< orphan*/  CG_HarvesterSkulls (TYPE_1__*,float,int /*<<< orphan*/ ,int,int) ; 
#define  CG_IMPRESSIVE 163 
#define  CG_KILLER 162 
#define  CG_ONEFLAG_STATUS 161 
 int /*<<< orphan*/  CG_OneFlagStatus (TYPE_1__*) ; 
#define  CG_PERFECT 160 
#define  CG_PLAYER_AMMO_ICON 159 
#define  CG_PLAYER_AMMO_ICON2D 158 
#define  CG_PLAYER_AMMO_VALUE 157 
#define  CG_PLAYER_ARMOR_ICON 156 
#define  CG_PLAYER_ARMOR_ICON2D 155 
#define  CG_PLAYER_ARMOR_VALUE 154 
#define  CG_PLAYER_HASFLAG 153 
#define  CG_PLAYER_HASFLAG2D 152 
#define  CG_PLAYER_HEAD 151 
#define  CG_PLAYER_HEALTH 150 
#define  CG_PLAYER_ITEM 149 
#define  CG_PLAYER_LOCATION 148 
#define  CG_PLAYER_SCORE 147 
#define  CG_PLAYER_STATUS 146 
#define  CG_RED_FLAGHEAD 145 
#define  CG_RED_FLAGNAME 144 
#define  CG_RED_FLAGSTATUS 143 
#define  CG_RED_NAME 142 
#define  CG_RED_SCORE 141 
#define  CG_SELECTEDPLAYER_ARMOR 140 
#define  CG_SELECTEDPLAYER_HEAD 139 
#define  CG_SELECTEDPLAYER_HEALTH 138 
#define  CG_SELECTEDPLAYER_LOCATION 137 
#define  CG_SELECTEDPLAYER_NAME 136 
#define  CG_SELECTEDPLAYER_POWERUP 135 
#define  CG_SELECTEDPLAYER_STATUS 134 
#define  CG_SELECTEDPLAYER_WEAPON 133 
 int CG_SHOW_2DONLY ; 
#define  CG_SPECTATORS 132 
#define  CG_TEAMINFO 131 
#define  CG_TEAM_COLOR 130 
#define  CG_VOICE_HEAD 129 
#define  CG_VOICE_NAME 128 
 TYPE_3__ cg_currentSelectedPlayer ; 
 TYPE_2__ cg_drawStatus ; 
 int /*<<< orphan*/  numSortedTeamPlayers ; 
 int qfalse ; 
 int qtrue ; 

void CG_OwnerDraw(float x, float y, float w, float h, float text_x, float text_y, int ownerDraw, int ownerDrawFlags, int align, float special, float scale, vec4_t color, qhandle_t shader, int textStyle) {
	rectDef_t rect;

  if ( cg_drawStatus.integer == 0 ) {
		return;
	}

	//if (ownerDrawFlags != 0 && !CG_OwnerDrawVisible(ownerDrawFlags)) {
	//	return;
	//}

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  switch (ownerDraw) {
  case CG_PLAYER_ARMOR_ICON:
    CG_DrawPlayerArmorIcon(&rect, ownerDrawFlags & CG_SHOW_2DONLY);
    break;
  case CG_PLAYER_ARMOR_ICON2D:
    CG_DrawPlayerArmorIcon(&rect, qtrue);
    break;
  case CG_PLAYER_ARMOR_VALUE:
    CG_DrawPlayerArmorValue(&rect, scale, color, shader, textStyle);
    break;
  case CG_PLAYER_AMMO_ICON:
    CG_DrawPlayerAmmoIcon(&rect, ownerDrawFlags & CG_SHOW_2DONLY);
    break;
  case CG_PLAYER_AMMO_ICON2D:
    CG_DrawPlayerAmmoIcon(&rect, qtrue);
    break;
  case CG_PLAYER_AMMO_VALUE:
    CG_DrawPlayerAmmoValue(&rect, scale, color, shader, textStyle);
    break;
  case CG_SELECTEDPLAYER_HEAD:
    CG_DrawSelectedPlayerHead(&rect, ownerDrawFlags & CG_SHOW_2DONLY, qfalse);
    break;
  case CG_VOICE_HEAD:
    CG_DrawSelectedPlayerHead(&rect, ownerDrawFlags & CG_SHOW_2DONLY, qtrue);
    break;
  case CG_VOICE_NAME:
    CG_DrawSelectedPlayerName(&rect, scale, color, qtrue, textStyle);
    break;
  case CG_SELECTEDPLAYER_STATUS:
    CG_DrawSelectedPlayerStatus(&rect);
    break;
  case CG_SELECTEDPLAYER_ARMOR:
    CG_DrawSelectedPlayerArmor(&rect, scale, color, shader, textStyle);
    break;
  case CG_SELECTEDPLAYER_HEALTH:
    CG_DrawSelectedPlayerHealth(&rect, scale, color, shader, textStyle);
    break;
  case CG_SELECTEDPLAYER_NAME:
    CG_DrawSelectedPlayerName(&rect, scale, color, qfalse, textStyle);
    break;
  case CG_SELECTEDPLAYER_LOCATION:
    CG_DrawSelectedPlayerLocation(&rect, scale, color, textStyle);
    break;
  case CG_SELECTEDPLAYER_WEAPON:
    CG_DrawSelectedPlayerWeapon(&rect);
    break;
  case CG_SELECTEDPLAYER_POWERUP:
    CG_DrawSelectedPlayerPowerup(&rect, ownerDrawFlags & CG_SHOW_2DONLY);
    break;
  case CG_PLAYER_HEAD:
    CG_DrawPlayerHead(&rect, ownerDrawFlags & CG_SHOW_2DONLY);
    break;
  case CG_PLAYER_ITEM:
    CG_DrawPlayerItem(&rect, scale, ownerDrawFlags & CG_SHOW_2DONLY);
    break;
  case CG_PLAYER_SCORE:
    CG_DrawPlayerScore(&rect, scale, color, shader, textStyle);
    break;
  case CG_PLAYER_HEALTH:
    CG_DrawPlayerHealth(&rect, scale, color, shader, textStyle);
    break;
  case CG_RED_SCORE:
    CG_DrawRedScore(&rect, scale, color, shader, textStyle);
    break;
  case CG_BLUE_SCORE:
    CG_DrawBlueScore(&rect, scale, color, shader, textStyle);
    break;
  case CG_RED_NAME:
    CG_DrawRedName(&rect, scale, color, textStyle);
    break;
  case CG_BLUE_NAME:
    CG_DrawBlueName(&rect, scale, color, textStyle);
    break;
  case CG_BLUE_FLAGHEAD:
    CG_DrawBlueFlagHead(&rect);
    break;
  case CG_BLUE_FLAGSTATUS:
    CG_DrawBlueFlagStatus(&rect, shader);
    break;
  case CG_BLUE_FLAGNAME:
    CG_DrawBlueFlagName(&rect, scale, color, textStyle);
    break;
  case CG_RED_FLAGHEAD:
    CG_DrawRedFlagHead(&rect);
    break;
  case CG_RED_FLAGSTATUS:
    CG_DrawRedFlagStatus(&rect, shader);
    break;
  case CG_RED_FLAGNAME:
    CG_DrawRedFlagName(&rect, scale, color, textStyle);
    break;
  case CG_HARVESTER_SKULLS:
    CG_HarvesterSkulls(&rect, scale, color, qfalse, textStyle);
    break;
  case CG_HARVESTER_SKULLS2D:
    CG_HarvesterSkulls(&rect, scale, color, qtrue, textStyle);
    break;
  case CG_ONEFLAG_STATUS:
    CG_OneFlagStatus(&rect);
    break;
  case CG_PLAYER_LOCATION:
    CG_DrawPlayerLocation(&rect, scale, color, textStyle);
    break;
  case CG_TEAM_COLOR:
    CG_DrawTeamColor(&rect, color);
    break;
  case CG_CTF_POWERUP:
    CG_DrawCTFPowerUp(&rect);
    break;
  case CG_AREA_POWERUP:
		CG_DrawAreaPowerUp(&rect, align, special, scale, color);
    break;
  case CG_PLAYER_STATUS:
    CG_DrawPlayerStatus(&rect);
    break;
  case CG_PLAYER_HASFLAG:
    CG_DrawPlayerHasFlag(&rect, qfalse);
    break;
  case CG_PLAYER_HASFLAG2D:
    CG_DrawPlayerHasFlag(&rect, qtrue);
    break;
  case CG_AREA_SYSTEMCHAT:
    CG_DrawAreaSystemChat(&rect, scale, color, shader);
    break;
  case CG_AREA_TEAMCHAT:
    CG_DrawAreaTeamChat(&rect, scale, color, shader);
    break;
  case CG_AREA_CHAT:
    CG_DrawAreaChat(&rect, scale, color, shader);
    break;
  case CG_GAME_TYPE:
    CG_DrawGameType(&rect, scale, color, shader, textStyle);
    break;
  case CG_GAME_STATUS:
    CG_DrawGameStatus(&rect, scale, color, shader, textStyle);
		break;
  case CG_KILLER:
    CG_DrawKiller(&rect, scale, color, shader, textStyle);
		break;
	case CG_ACCURACY:
	case CG_ASSISTS:
	case CG_DEFEND:
	case CG_EXCELLENT:
	case CG_IMPRESSIVE:
	case CG_PERFECT:
	case CG_GAUNTLET:
	case CG_CAPTURES:
		CG_DrawMedal(ownerDraw, &rect, scale, color, shader);
		break;
  case CG_SPECTATORS:
		CG_DrawTeamSpectators(&rect, scale, color, shader);
		break;
  case CG_TEAMINFO:
		if (cg_currentSelectedPlayer.integer == numSortedTeamPlayers) {
			CG_DrawNewTeamInfo(&rect, text_x, text_y, scale, color, shader);
		}
		break;
  case CG_CAPFRAGLIMIT:
    CG_DrawCapFragLimit(&rect, scale, color, shader, textStyle);
		break;
  case CG_1STPLACE:
    CG_Draw1stPlace(&rect, scale, color, shader, textStyle);
		break;
  case CG_2NDPLACE:
    CG_Draw2ndPlace(&rect, scale, color, shader, textStyle);
		break;
  default:
    break;
  }
}