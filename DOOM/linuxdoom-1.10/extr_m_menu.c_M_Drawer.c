#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {short x; short y; short numitems; TYPE_1__* menuitems; int /*<<< orphan*/  (* routine ) () ;} ;
struct TYPE_5__ {int /*<<< orphan*/  height; } ;
struct TYPE_4__ {scalar_t__* name; } ;

/* Variables and functions */
 short LINEHEIGHT ; 
 int M_StringHeight (char*) ; 
 int M_StringWidth (char*) ; 
 int /*<<< orphan*/  M_WriteText (short,short,char*) ; 
 int /*<<< orphan*/  PU_CACHE ; 
 scalar_t__ SHORT (int /*<<< orphan*/ ) ; 
 short SKULLXOFF ; 
 int /*<<< orphan*/  V_DrawPatchDirect (short,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W_CacheLumpName (scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* currentMenu ; 
 TYPE_2__** hu_font ; 
 int inhelpscreens ; 
 short itemOn ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menuactive ; 
 char* messageString ; 
 scalar_t__ messageToPrint ; 
 scalar_t__** skullName ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 short strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,short) ; 
 int /*<<< orphan*/  stub1 () ; 
 size_t whichSkull ; 

void M_Drawer (void)
{
    static short	x;
    static short	y;
    short		i;
    short		max;
    char		string[40];
    int			start;

    inhelpscreens = false;

    
    // Horiz. & Vertically center string and print it.
    if (messageToPrint)
    {
	start = 0;
	y = 100 - M_StringHeight(messageString)/2;
	while(*(messageString+start))
	{
	    for (i = 0;i < strlen(messageString+start);i++)
		if (*(messageString+start+i) == '\n')
		{
		    memset(string,0,40);
		    strncpy(string,messageString+start,i);
		    start += i+1;
		    break;
		}
				
	    if (i == strlen(messageString+start))
	    {
		strcpy(string,messageString+start);
		start += i;
	    }
				
	    x = 160 - M_StringWidth(string)/2;
	    M_WriteText(x,y,string);
	    y += SHORT(hu_font[0]->height);
	}
	return;
    }

    if (!menuactive)
	return;

    if (currentMenu->routine)
	currentMenu->routine();         // call Draw routine
    
    // DRAW MENU
    x = currentMenu->x;
    y = currentMenu->y;
    max = currentMenu->numitems;

    for (i=0;i<max;i++)
    {
	if (currentMenu->menuitems[i].name[0])
	    V_DrawPatchDirect (x,y,0,
			       W_CacheLumpName(currentMenu->menuitems[i].name ,PU_CACHE));
	y += LINEHEIGHT;
    }

    
    // DRAW SKULL
    V_DrawPatchDirect(x + SKULLXOFF,currentMenu->y - 5 + itemOn*LINEHEIGHT, 0,
		      W_CacheLumpName(skullName[whichSkull],PU_CACHE));

}