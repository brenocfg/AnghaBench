#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  patch_t ;
struct TYPE_4__ {int nanims; void** p; } ;
typedef  TYPE_1__ anim_t ;
struct TYPE_5__ {int epsd; } ;

/* Variables and functions */
 int MAXPLAYERS ; 
 int* NUMANIMS ; 
 int NUMCMAPS ; 
 int NUMMAPS ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  PU_STATIC ; 
 int /*<<< orphan*/  V_DrawPatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 void* W_CacheLumpName (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** anims ; 
 void* bg ; 
 void** bp ; 
 void* bstar ; 
 void* colon ; 
 scalar_t__ commercial ; 
 int /*<<< orphan*/  deathmatch ; 
 void* entering ; 
 void* finished ; 
 void* frags ; 
 scalar_t__ french ; 
 scalar_t__ gamemode ; 
 void* items ; 
 void* killers ; 
 void* kills ; 
 int /*<<< orphan*/ ** lnames ; 
 scalar_t__ netgame ; 
 void** num ; 
 void** p ; 
 void* par ; 
 void* percent ; 
 scalar_t__ retail ; 
 void* secret ; 
 void* sp_secret ; 
 void* splat ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 void* star ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 void* sucks ; 
 void* time ; 
 void* total ; 
 void* victims ; 
 TYPE_2__* wbs ; 
 void* wiminus ; 
 void** yah ; 

void WI_loadData(void)
{
    int		i;
    int		j;
    char	name[9];
    anim_t*	a;

    if (gamemode == commercial)
	strcpy(name, "INTERPIC");
    else 
	sprintf(name, "WIMAP%d", wbs->epsd);
    
    if ( gamemode == retail )
    {
      if (wbs->epsd == 3)
	strcpy(name,"INTERPIC");
    }

    // background
    bg = W_CacheLumpName(name, PU_CACHE);    
    V_DrawPatch(0, 0, 1, bg);


    // UNUSED unsigned char *pic = screens[1];
    // if (gamemode == commercial)
    // {
    // darken the background image
    // while (pic != screens[1] + SCREENHEIGHT*SCREENWIDTH)
    // {
    //   *pic = colormaps[256*25 + *pic];
    //   pic++;
    // }
    //}

    if (gamemode == commercial)
    {
	NUMCMAPS = 32;								
	lnames = (patch_t **) Z_Malloc(sizeof(patch_t*) * NUMCMAPS,
				       PU_STATIC, 0);
	for (i=0 ; i<NUMCMAPS ; i++)
	{								
	    sprintf(name, "CWILV%2.2d", i);
	    lnames[i] = W_CacheLumpName(name, PU_STATIC);
	}					
    }
    else
    {
	lnames = (patch_t **) Z_Malloc(sizeof(patch_t*) * NUMMAPS,
				       PU_STATIC, 0);
	for (i=0 ; i<NUMMAPS ; i++)
	{
	    sprintf(name, "WILV%d%d", wbs->epsd, i);
	    lnames[i] = W_CacheLumpName(name, PU_STATIC);
	}

	// you are here
	yah[0] = W_CacheLumpName("WIURH0", PU_STATIC);

	// you are here (alt.)
	yah[1] = W_CacheLumpName("WIURH1", PU_STATIC);

	// splat
	splat = W_CacheLumpName("WISPLAT", PU_STATIC); 
	
	if (wbs->epsd < 3)
	{
	    for (j=0;j<NUMANIMS[wbs->epsd];j++)
	    {
		a = &anims[wbs->epsd][j];
		for (i=0;i<a->nanims;i++)
		{
		    // MONDO HACK!
		    if (wbs->epsd != 1 || j != 8) 
		    {
			// animations
			sprintf(name, "WIA%d%.2d%.2d", wbs->epsd, j, i);  
			a->p[i] = W_CacheLumpName(name, PU_STATIC);
		    }
		    else
		    {
			// HACK ALERT!
			a->p[i] = anims[1][4].p[i]; 
		    }
		}
	    }
	}
    }

    // More hacks on minus sign.
    wiminus = W_CacheLumpName("WIMINUS", PU_STATIC); 

    for (i=0;i<10;i++)
    {
	 // numbers 0-9
	sprintf(name, "WINUM%d", i);     
	num[i] = W_CacheLumpName(name, PU_STATIC);
    }

    // percent sign
    percent = W_CacheLumpName("WIPCNT", PU_STATIC);

    // "finished"
    finished = W_CacheLumpName("WIF", PU_STATIC);

    // "entering"
    entering = W_CacheLumpName("WIENTER", PU_STATIC);

    // "kills"
    kills = W_CacheLumpName("WIOSTK", PU_STATIC);   

    // "scrt"
    secret = W_CacheLumpName("WIOSTS", PU_STATIC);

     // "secret"
    sp_secret = W_CacheLumpName("WISCRT2", PU_STATIC);

    // Yuck. 
    if (french)
    {
	// "items"
	if (netgame && !deathmatch)
	    items = W_CacheLumpName("WIOBJ", PU_STATIC);    
  	else
	    items = W_CacheLumpName("WIOSTI", PU_STATIC);
    } else
	items = W_CacheLumpName("WIOSTI", PU_STATIC);

    // "frgs"
    frags = W_CacheLumpName("WIFRGS", PU_STATIC);    

    // ":"
    colon = W_CacheLumpName("WICOLON", PU_STATIC); 

    // "time"
    time = W_CacheLumpName("WITIME", PU_STATIC);   

    // "sucks"
    sucks = W_CacheLumpName("WISUCKS", PU_STATIC);  

    // "par"
    par = W_CacheLumpName("WIPAR", PU_STATIC);   

    // "killers" (vertical)
    killers = W_CacheLumpName("WIKILRS", PU_STATIC);

    // "victims" (horiz)
    victims = W_CacheLumpName("WIVCTMS", PU_STATIC);

    // "total"
    total = W_CacheLumpName("WIMSTT", PU_STATIC);   

    // your face
    star = W_CacheLumpName("STFST01", PU_STATIC);

    // dead face
    bstar = W_CacheLumpName("STFDEAD0", PU_STATIC);    

    for (i=0 ; i<MAXPLAYERS ; i++)
    {
	// "1,2,3,4"
	sprintf(name, "STPB%d", i);      
	p[i] = W_CacheLumpName(name, PU_STATIC);

	// "1,2,3,4"
	sprintf(name, "WIBP%d", i+1);     
	bp[i] = W_CacheLumpName(name, PU_STATIC);
    }

}