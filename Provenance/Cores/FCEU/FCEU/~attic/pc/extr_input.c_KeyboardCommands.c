#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int BACKSLASH ; 
 int BACKSPACE ; 
 int* BWorldData ; 
 int /*<<< orphan*/  CloseGame () ; 
 int DIPS ; 
 int /*<<< orphan*/  DecreaseEmulationSpeed () ; 
 int /*<<< orphan*/  DoCheatSeq () ; 
 int ENTER ; 
 int EQUAL ; 
 int ESCAPE ; 
 int F1 ; 
 int F10 ; 
 int F11 ; 
 int F12 ; 
 int F2 ; 
 int F3 ; 
 int F4 ; 
 int F5 ; 
 int F6 ; 
 int F7 ; 
 int F8 ; 
 int F9 ; 
 int /*<<< orphan*/  FCEUI_DatachSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCEUI_DispMessage (char*,...) ; 
 int /*<<< orphan*/  FCEUI_FDSInsert () ; 
 int /*<<< orphan*/  FCEUI_FDSSelect () ; 
 int /*<<< orphan*/  FCEUI_FrameAdvance () ; 
 int /*<<< orphan*/  FCEUI_LoadMovie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCEUI_LoadState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCEUI_MovieToggleFrameDisplay () ; 
 int /*<<< orphan*/  FCEUI_NTSCDEC () ; 
 int /*<<< orphan*/  FCEUI_NTSCINC () ; 
 int /*<<< orphan*/  FCEUI_NTSCSELHUE () ; 
 int /*<<< orphan*/  FCEUI_NTSCSELTINT () ; 
 int /*<<< orphan*/  FCEUI_PowerNES () ; 
 int /*<<< orphan*/  FCEUI_ResetNES () ; 
 int /*<<< orphan*/  FCEUI_SaveMovie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCEUI_SaveSnapshot () ; 
 int /*<<< orphan*/  FCEUI_SaveState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCEUI_SetRenderDisable (int,int) ; 
 int /*<<< orphan*/  FCEUI_ToggleEmulationPause () ; 
 int /*<<< orphan*/  FCEUI_ToggleTileView () ; 
 int /*<<< orphan*/  FCEUI_VSUniCoin () ; 
 int /*<<< orphan*/  FCEUI_VSUniToggleDIP (int) ; 
 int /*<<< orphan*/  FCEUI_VSUniToggleDIPView () ; 
 scalar_t__ GIT_FDS ; 
 scalar_t__ GIT_NSF ; 
 scalar_t__ GIT_VSUNI ; 
 int GRAVE ; 
 int /*<<< orphan*/  GUI_Hide (int) ; 
 int /*<<< orphan*/  GUI_RequestExit () ; 
 int /*<<< orphan*/  GetKeyboard () ; 
 int H ; 
 int /*<<< orphan*/  IncreaseEmulationSpeed () ; 
 scalar_t__* InputType ; 
 int KEY (int) ; 
 int KP_MINUS ; 
 int KP_PLUS ; 
 int LEFTALT ; 
 int LEFTSHIFT ; 
 int MINUS ; 
 int NoWaiting ; 
 int RIGHTALT ; 
 int RIGHTCONTROL ; 
 int RIGHTSHIFT ; 
 int SCROLLLOCK ; 
 int /*<<< orphan*/  SDL_GRAB_OFF ; 
 int /*<<< orphan*/  SDL_GRAB_ON ; 
 int /*<<< orphan*/  SDL_WM_GrabInput (int /*<<< orphan*/ ) ; 
 scalar_t__ SIFC_BWORLD ; 
 scalar_t__ SIFC_FKB ; 
 scalar_t__ SIS_DATACH ; 
 int /*<<< orphan*/  SSM (int) ; 
 int T ; 
 int /*<<< orphan*/  ToggleFS () ; 
 int cidisabled ; 
 scalar_t__ cspec ; 
 scalar_t__ gametype ; 
 scalar_t__ keyonly (int) ; 
 int /*<<< orphan*/  keys ; 
 int /*<<< orphan*/  strcpy (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void KeyboardCommands(void)
{
  int is_shift, is_alt;

  keys=GetKeyboard(); 

  if(InputType[2]==SIFC_FKB)
  {
   if(keyonly(SCROLLLOCK)) 
   {
    cidisabled^=1;
    FCEUI_DispMessage("Family Keyboard %sabled.",cidisabled?"en":"dis");
   }
   #ifdef SDL
   SDL_WM_GrabInput(cidisabled?SDL_GRAB_ON:SDL_GRAB_OFF);
   #endif
   if(cidisabled) return;
  }

  is_shift = KEY(LEFTSHIFT) | KEY(RIGHTSHIFT);
  is_alt = KEY(LEFTALT) | KEY(RIGHTALT);

  if(keyonly(F4))
  {
   if(is_shift) FCEUI_SetRenderDisable(-1, 2);
   else FCEUI_SetRenderDisable(2, -1);
  }
  #ifdef SDL
  if(keyonly(ENTER) && is_alt) ToggleFS();
  #endif

  NoWaiting&=~1;
  if(KEY(GRAVE))
   NoWaiting|=1;

  if(gametype==GIT_FDS)
  {
   if(keyonly(F6)) FCEUI_FDSSelect();
   if(keyonly(F8)) FCEUI_FDSInsert();
  }

  if(keyonly(F9)) FCEUI_SaveSnapshot();
  if(gametype!=GIT_NSF)
  {
   #ifndef EXTGUI
   if(keyonly(F2)) DoCheatSeq();
   #endif
   if(keyonly(F5)) 
   {
    if(is_shift)
     FCEUI_SaveMovie(NULL,0,NULL);
    else
     FCEUI_SaveState(NULL);
   }
   if(keyonly(F7)) 
   {
    if(is_shift)
     FCEUI_LoadMovie(NULL,0);
    else
     FCEUI_LoadState(NULL);
   }
  }

  if(keyonly(F1)) FCEUI_ToggleTileView();

  if(keyonly(MINUS)) DecreaseEmulationSpeed();
  if(keyonly(EQUAL)) IncreaseEmulationSpeed();
  if(keyonly(BACKSPACE)) FCEUI_MovieToggleFrameDisplay();
  if(keyonly(BACKSLASH)) FCEUI_ToggleEmulationPause();
  if(keyonly(RIGHTCONTROL)) FCEUI_FrameAdvance();

  if(keyonly(F10)) FCEUI_ResetNES();
  if(keyonly(F11)) FCEUI_PowerNES();

  #ifdef EXTGUI
  if(keyonly(F3)) GUI_Hide(-1);
  if(KEY(F12)) GUI_RequestExit();
  if(KEY(ESCAPE)) CloseGame();
  #else
  if(KEY(F12) || KEY(ESCAPE)) CloseGame();
  #endif

  if(gametype==GIT_VSUNI)
  {
	if(keyonly(F8)) FCEUI_VSUniCoin();
	if(keyonly(F6))
        {
	 DIPS^=1;
	 FCEUI_VSUniToggleDIPView();
	}
	if(!(DIPS&1)) goto DIPSless;
	if(keyonly(1)) FCEUI_VSUniToggleDIP(0);
	if(keyonly(2)) FCEUI_VSUniToggleDIP(1);
	if(keyonly(3)) FCEUI_VSUniToggleDIP(2);
	if(keyonly(4)) FCEUI_VSUniToggleDIP(3);
	if(keyonly(5)) FCEUI_VSUniToggleDIP(4);
	if(keyonly(6)) FCEUI_VSUniToggleDIP(5);
	if(keyonly(7)) FCEUI_VSUniToggleDIP(6);
	if(keyonly(8)) FCEUI_VSUniToggleDIP(7);
  }
  else
  {
   static uint8 bbuf[32];
   static int bbuft;
   static int barcoder = 0;

   if(keyonly(H)) FCEUI_NTSCSELHUE();
   if(keyonly(T)) FCEUI_NTSCSELTINT();
   if(KEY(KP_MINUS) || KEY(MINUS)) FCEUI_NTSCDEC();
   if(KEY(KP_PLUS) || KEY(EQUAL)) FCEUI_NTSCINC();

   if((InputType[2] == SIFC_BWORLD) || (cspec == SIS_DATACH))
   {
    if(keyonly(F8)) 
    {
     barcoder ^= 1;
     if(!barcoder)
     {
      if(InputType[2] == SIFC_BWORLD)
      {
       strcpy(&BWorldData[1],bbuf);
       BWorldData[0]=1;
      }
      else
       FCEUI_DatachSet(bbuf);
      FCEUI_DispMessage("Barcode Entered");
     } 
     else { bbuft = 0; FCEUI_DispMessage("Enter Barcode");}
    }
   } else barcoder = 0;

	#define SSM(x)		\
	{ if(barcoder) { if(bbuft < 13) {bbuf[bbuft++] = '0' + x; bbuf[bbuft] = 0;} FCEUI_DispMessage("Barcode: %s",bbuf);}	\
	else { 			\
	 if(is_shift) FCEUI_SelectMovie(x,1); 	\
	 else FCEUI_SelectState(x,1); 	\
	} }

   DIPSless:
   if(keyonly(0)) SSM(0);
   if(keyonly(1)) SSM(1);
   if(keyonly(2)) SSM(2);
   if(keyonly(3)) SSM(3);
   if(keyonly(4)) SSM(4);
   if(keyonly(5)) SSM(5);
   if(keyonly(6)) SSM(6);
   if(keyonly(7)) SSM(7);
   if(keyonly(8)) SSM(8);
   if(keyonly(9)) SSM(9);
   #undef SSM
 }
}