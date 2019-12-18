#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_44__ {float x; float y; float w; float h; } ;
typedef  TYPE_1__ rectDef_t ;
typedef  int /*<<< orphan*/  qhandle_t ;

/* Variables and functions */
#define  UI_ALLMAPS_SELECTION 183 
#define  UI_BLUETEAM1 182 
#define  UI_BLUETEAM2 181 
#define  UI_BLUETEAM3 180 
#define  UI_BLUETEAM4 179 
#define  UI_BLUETEAM5 178 
#define  UI_BLUETEAMNAME 177 
#define  UI_BOTNAME 176 
#define  UI_BOTSKILL 175 
#define  UI_CLANCINEMATIC 174 
#define  UI_CLANLOGO 173 
#define  UI_CLANNAME 172 
#define  UI_CROSSHAIR 171 
 int /*<<< orphan*/  UI_DrawAllMapsSelection (TYPE_1__*,float,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawBotName (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawBotSkill (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawClanCinematic (TYPE_1__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawClanLogo (TYPE_1__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawClanName (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawCrosshair (TYPE_1__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawEffects (TYPE_1__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawGLInfo (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawGameType (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawHandicap (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawJoinGameType (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawKeyBindStatus (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawMapCinematic (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawMapPreview (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawMapTimeToBeat (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawNetFilter (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawNetGameType (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawNetMapCinematic (TYPE_1__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawNetMapPreview (TYPE_1__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawNetSource (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawOpponent (TYPE_1__*) ; 
 int /*<<< orphan*/  UI_DrawOpponentLogo (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawOpponentLogoMetal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawOpponentLogoName (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawOpponentName (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawPlayerLogo (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawPlayerLogoMetal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawPlayerLogoName (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawPlayerModel (TYPE_1__*) ; 
 int /*<<< orphan*/  UI_DrawPreviewCinematic (TYPE_1__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawRedBlue (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawSelectedPlayer (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawServerMOTD (TYPE_1__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawServerRefreshDate (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawSkill (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawTeamMember (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawTeamName (TYPE_1__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawTier (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawTierGameType (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_DrawTierMap (TYPE_1__*,int) ; 
 int /*<<< orphan*/  UI_DrawTierMapName (TYPE_1__*,float,int /*<<< orphan*/ ,int) ; 
#define  UI_EFFECTS 170 
#define  UI_GAMETYPE 169 
#define  UI_GLINFO 168 
#define  UI_HANDICAP 167 
#define  UI_JOINGAMETYPE 166 
#define  UI_KEYBINDSTATUS 165 
#define  UI_MAPCINEMATIC 164 
#define  UI_MAPPREVIEW 163 
#define  UI_MAPS_SELECTION 162 
#define  UI_MAP_TIMETOBEAT 161 
#define  UI_NETFILTER 160 
#define  UI_NETGAMETYPE 159 
#define  UI_NETMAPCINEMATIC 158 
#define  UI_NETMAPPREVIEW 157 
#define  UI_NETSOURCE 156 
#define  UI_OPPONENTLOGO 155 
#define  UI_OPPONENTLOGO_METAL 154 
#define  UI_OPPONENTLOGO_NAME 153 
#define  UI_OPPONENTMODEL 152 
#define  UI_OPPONENT_NAME 151 
#define  UI_PLAYERLOGO 150 
#define  UI_PLAYERLOGO_METAL 149 
#define  UI_PLAYERLOGO_NAME 148 
#define  UI_PLAYERMODEL 147 
#define  UI_PREVIEWCINEMATIC 146 
#define  UI_REDBLUE 145 
#define  UI_REDTEAM1 144 
#define  UI_REDTEAM2 143 
#define  UI_REDTEAM3 142 
#define  UI_REDTEAM4 141 
#define  UI_REDTEAM5 140 
#define  UI_REDTEAMNAME 139 
#define  UI_SELECTEDPLAYER 138 
#define  UI_SERVERMOTD 137 
#define  UI_SERVERREFRESHDATE 136 
#define  UI_SKILL 135 
#define  UI_STARTMAPCINEMATIC 134 
#define  UI_TIER 133 
#define  UI_TIERMAP1 132 
#define  UI_TIERMAP2 131 
#define  UI_TIERMAP3 130 
#define  UI_TIER_GAMETYPE 129 
#define  UI_TIER_MAPNAME 128 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void UI_OwnerDraw(float x, float y, float w, float h, float text_x, float text_y, int ownerDraw, int ownerDrawFlags, int align, float special, float scale, vec4_t color, qhandle_t shader, int textStyle) {
	rectDef_t rect;

  rect.x = x + text_x;
  rect.y = y + text_y;
  rect.w = w;
  rect.h = h;

  switch (ownerDraw) {
    case UI_HANDICAP:
      UI_DrawHandicap(&rect, scale, color, textStyle);
      break;
    case UI_EFFECTS:
      UI_DrawEffects(&rect, scale, color);
      break;
    case UI_PLAYERMODEL:
      UI_DrawPlayerModel(&rect);
      break;
    case UI_CLANNAME:
      UI_DrawClanName(&rect, scale, color, textStyle);
      break;
    case UI_CLANLOGO:
      UI_DrawClanLogo(&rect, scale, color);
      break;
    case UI_CLANCINEMATIC:
      UI_DrawClanCinematic(&rect, scale, color);
      break;
    case UI_PREVIEWCINEMATIC:
      UI_DrawPreviewCinematic(&rect, scale, color);
      break;
    case UI_GAMETYPE:
      UI_DrawGameType(&rect, scale, color, textStyle);
      break;
    case UI_NETGAMETYPE:
      UI_DrawNetGameType(&rect, scale, color, textStyle);
      break;
    case UI_JOINGAMETYPE:
	  UI_DrawJoinGameType(&rect, scale, color, textStyle);
	  break;
    case UI_MAPPREVIEW:
      UI_DrawMapPreview(&rect, scale, color, qtrue);
      break;
    case UI_MAP_TIMETOBEAT:
      UI_DrawMapTimeToBeat(&rect, scale, color, textStyle);
      break;
    case UI_MAPCINEMATIC:
      UI_DrawMapCinematic(&rect, scale, color, qfalse);
      break;
    case UI_STARTMAPCINEMATIC:
      UI_DrawMapCinematic(&rect, scale, color, qtrue);
      break;
    case UI_SKILL:
      UI_DrawSkill(&rect, scale, color, textStyle);
      break;
    case UI_BLUETEAMNAME:
      UI_DrawTeamName(&rect, scale, color, qtrue, textStyle);
      break;
    case UI_REDTEAMNAME:
      UI_DrawTeamName(&rect, scale, color, qfalse, textStyle);
      break;
    case UI_BLUETEAM1:
		case UI_BLUETEAM2:
		case UI_BLUETEAM3:
		case UI_BLUETEAM4:
		case UI_BLUETEAM5:
      UI_DrawTeamMember(&rect, scale, color, qtrue, ownerDraw - UI_BLUETEAM1 + 1, textStyle);
      break;
    case UI_REDTEAM1:
		case UI_REDTEAM2:
		case UI_REDTEAM3:
		case UI_REDTEAM4:
		case UI_REDTEAM5:
      UI_DrawTeamMember(&rect, scale, color, qfalse, ownerDraw - UI_REDTEAM1 + 1, textStyle);
      break;
		case UI_NETSOURCE:
      UI_DrawNetSource(&rect, scale, color, textStyle);
			break;
    case UI_NETMAPPREVIEW:
      UI_DrawNetMapPreview(&rect, scale, color);
      break;
    case UI_NETMAPCINEMATIC:
      UI_DrawNetMapCinematic(&rect, scale, color);
      break;
		case UI_NETFILTER:
      UI_DrawNetFilter(&rect, scale, color, textStyle);
			break;
		case UI_TIER:
			UI_DrawTier(&rect, scale, color, textStyle);
			break;
		case UI_OPPONENTMODEL:
			UI_DrawOpponent(&rect);
			break;
		case UI_TIERMAP1:
			UI_DrawTierMap(&rect, 0);
			break;
		case UI_TIERMAP2:
			UI_DrawTierMap(&rect, 1);
			break;
		case UI_TIERMAP3:
			UI_DrawTierMap(&rect, 2);
			break;
		case UI_PLAYERLOGO:
			UI_DrawPlayerLogo(&rect, color);
			break;
		case UI_PLAYERLOGO_METAL:
			UI_DrawPlayerLogoMetal(&rect, color);
			break;
		case UI_PLAYERLOGO_NAME:
			UI_DrawPlayerLogoName(&rect, color);
			break;
		case UI_OPPONENTLOGO:
			UI_DrawOpponentLogo(&rect, color);
			break;
		case UI_OPPONENTLOGO_METAL:
			UI_DrawOpponentLogoMetal(&rect, color);
			break;
		case UI_OPPONENTLOGO_NAME:
			UI_DrawOpponentLogoName(&rect, color);
			break;
		case UI_TIER_MAPNAME:
			UI_DrawTierMapName(&rect, scale, color, textStyle);
			break;
		case UI_TIER_GAMETYPE:
			UI_DrawTierGameType(&rect, scale, color, textStyle);
			break;
		case UI_ALLMAPS_SELECTION:
			UI_DrawAllMapsSelection(&rect, scale, color, textStyle, qtrue);
			break;
		case UI_MAPS_SELECTION:
			UI_DrawAllMapsSelection(&rect, scale, color, textStyle, qfalse);
			break;
		case UI_OPPONENT_NAME:
			UI_DrawOpponentName(&rect, scale, color, textStyle);
			break;
		case UI_BOTNAME:
			UI_DrawBotName(&rect, scale, color, textStyle);
			break;
		case UI_BOTSKILL:
			UI_DrawBotSkill(&rect, scale, color, textStyle);
			break;
		case UI_REDBLUE:
			UI_DrawRedBlue(&rect, scale, color, textStyle);
			break;
		case UI_CROSSHAIR:
			UI_DrawCrosshair(&rect, scale, color);
			break;
		case UI_SELECTEDPLAYER:
			UI_DrawSelectedPlayer(&rect, scale, color, textStyle);
			break;
		case UI_SERVERREFRESHDATE:
			UI_DrawServerRefreshDate(&rect, scale, color, textStyle);
			break;
		case UI_SERVERMOTD:
			UI_DrawServerMOTD(&rect, scale, color);
			break;
		case UI_GLINFO:
			UI_DrawGLInfo(&rect,scale, color, textStyle);
			break;
		case UI_KEYBINDSTATUS:
			UI_DrawKeyBindStatus(&rect,scale, color, textStyle);
			break;
    default:
      break;
  }

}