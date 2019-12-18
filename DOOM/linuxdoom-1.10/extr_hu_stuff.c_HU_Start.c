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

/* Variables and functions */
 int /*<<< orphan*/  HU_FONTSTART ; 
 int /*<<< orphan*/  HU_INPUTX ; 
 int /*<<< orphan*/  HU_INPUTY ; 
 int /*<<< orphan*/  HU_MSGHEIGHT ; 
 int /*<<< orphan*/  HU_MSGX ; 
 int /*<<< orphan*/  HU_MSGY ; 
 int /*<<< orphan*/  HU_Stop () ; 
 char* HU_TITLE ; 
 char* HU_TITLE2 ; 
 int /*<<< orphan*/  HU_TITLEX ; 
 int /*<<< orphan*/  HU_TITLEY ; 
 int /*<<< orphan*/  HUlib_addCharToTextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUlib_initIText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  HUlib_initSText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  HUlib_initTextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXPLAYERS ; 
 int always_off ; 
 int chat_on ; 
#define  commercial 131 
 size_t consoleplayer ; 
 int gamemode ; 
 int headsupactive ; 
 int /*<<< orphan*/  hu_font ; 
 int message_dontfuckwithme ; 
 int message_nottobefuckedwith ; 
 int message_on ; 
 int /*<<< orphan*/ * players ; 
 int /*<<< orphan*/ * plr ; 
#define  registered 130 
#define  retail 129 
#define  shareware 128 
 int /*<<< orphan*/  w_chat ; 
 int /*<<< orphan*/ * w_inputbuffer ; 
 int /*<<< orphan*/  w_message ; 
 int /*<<< orphan*/  w_title ; 

void HU_Start(void)
{

    int		i;
    char*	s;

    if (headsupactive)
	HU_Stop();

    plr = &players[consoleplayer];
    message_on = false;
    message_dontfuckwithme = false;
    message_nottobefuckedwith = false;
    chat_on = false;

    // create the message widget
    HUlib_initSText(&w_message,
		    HU_MSGX, HU_MSGY, HU_MSGHEIGHT,
		    hu_font,
		    HU_FONTSTART, &message_on);

    // create the map title widget
    HUlib_initTextLine(&w_title,
		       HU_TITLEX, HU_TITLEY,
		       hu_font,
		       HU_FONTSTART);
    
    switch ( gamemode )
    {
      case shareware:
      case registered:
      case retail:
	s = HU_TITLE;
	break;

/* FIXME
      case pack_plut:
	s = HU_TITLEP;
	break;
      case pack_tnt:
	s = HU_TITLET;
	break;
*/
	
      case commercial:
      default:
	 s = HU_TITLE2;
	 break;
    }
    
    while (*s)
	HUlib_addCharToTextLine(&w_title, *(s++));

    // create the chat widget
    HUlib_initIText(&w_chat,
		    HU_INPUTX, HU_INPUTY,
		    hu_font,
		    HU_FONTSTART, &chat_on);

    // create the inputbuffer widgets
    for (i=0 ; i<MAXPLAYERS ; i++)
	HUlib_initIText(&w_inputbuffer[i], 0, 0, 0, 0, &always_off);

    headsupactive = true;

}