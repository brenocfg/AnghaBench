#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char chatchar; } ;
struct TYPE_12__ {TYPE_2__ cmd; } ;
struct TYPE_11__ {scalar_t__ message; } ;
struct TYPE_8__ {scalar_t__ l; scalar_t__ len; } ;
struct TYPE_10__ {TYPE_1__ l; } ;

/* Variables and functions */
 char HU_BROADCAST ; 
 scalar_t__ HU_MSGTIMEOUT ; 
 int /*<<< orphan*/  HUlib_addMessageToSText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int HUlib_keyInIText (TYPE_3__*,char) ; 
 int /*<<< orphan*/  HUlib_resetIText (TYPE_3__*) ; 
 char KEY_ENTER ; 
 int MAXPLAYERS ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* chat_dest ; 
 scalar_t__ commercial ; 
 int consoleplayer ; 
 scalar_t__ gamemode ; 
 scalar_t__ message_counter ; 
 int message_dontfuckwithme ; 
 int message_nottobefuckedwith ; 
 int message_on ; 
 scalar_t__ netgame ; 
 int /*<<< orphan*/ * player_names ; 
 int /*<<< orphan*/ * playeringame ; 
 TYPE_5__* players ; 
 TYPE_4__* plr ; 
 int /*<<< orphan*/  sfx_radio ; 
 int /*<<< orphan*/  sfx_tink ; 
 scalar_t__* shiftxform ; 
 scalar_t__ showMessages ; 
 TYPE_3__* w_inputbuffer ; 
 int /*<<< orphan*/  w_message ; 

void HU_Ticker(void)
{

    int i, rc;
    char c;

    // tick down message counter if message is up
    if (message_counter && !--message_counter)
    {
	message_on = false;
	message_nottobefuckedwith = false;
    }

    if (showMessages || message_dontfuckwithme)
    {

	// display message if necessary
	if ((plr->message && !message_nottobefuckedwith)
	    || (plr->message && message_dontfuckwithme))
	{
	    HUlib_addMessageToSText(&w_message, 0, plr->message);
	    plr->message = 0;
	    message_on = true;
	    message_counter = HU_MSGTIMEOUT;
	    message_nottobefuckedwith = message_dontfuckwithme;
	    message_dontfuckwithme = 0;
	}

    } // else message_on = false;

    // check for incoming chat characters
    if (netgame)
    {
	for (i=0 ; i<MAXPLAYERS; i++)
	{
	    if (!playeringame[i])
		continue;
	    if (i != consoleplayer
		&& (c = players[i].cmd.chatchar))
	    {
		if (c <= HU_BROADCAST)
		    chat_dest[i] = c;
		else
		{
		    if (c >= 'a' && c <= 'z')
			c = (char) shiftxform[(unsigned char) c];
		    rc = HUlib_keyInIText(&w_inputbuffer[i], c);
		    if (rc && c == KEY_ENTER)
		    {
			if (w_inputbuffer[i].l.len
			    && (chat_dest[i] == consoleplayer+1
				|| chat_dest[i] == HU_BROADCAST))
			{
			    HUlib_addMessageToSText(&w_message,
						    player_names[i],
						    w_inputbuffer[i].l.l);
			    
			    message_nottobefuckedwith = true;
			    message_on = true;
			    message_counter = HU_MSGTIMEOUT;
			    if ( gamemode == commercial )
			      S_StartSound(0, sfx_radio);
			    else
			      S_StartSound(0, sfx_tink);
			}
			HUlib_resetIText(&w_inputbuffer[i]);
		    }
		}
		players[i].cmd.chatchar = 0;
	    }
	}
    }

}