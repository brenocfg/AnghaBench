#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int episode; int /*<<< orphan*/  name2; int /*<<< orphan*/  name1; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*,int /*<<< orphan*/ ) ; 
 int MAXSWITCHES ; 
 scalar_t__ R_CheckTextureNumForName (int /*<<< orphan*/ ) ; 
 void* R_TextureNumForName (int /*<<< orphan*/ ) ; 
 TYPE_1__* alphSwitchList ; 
 scalar_t__ commercial ; 
 scalar_t__ gamemode ; 
 int numswitches ; 
 scalar_t__ registered ; 
 int* switchlist ; 

void P_InitSwitchList(void)
{
    int		i;
    int		index;
    int		episode;
	
    episode = 1;

    if (gamemode == registered)
	episode = 2;
    else
	if ( gamemode == commercial )
	    episode = 3;
		
    for (index = 0,i = 0;i < MAXSWITCHES;i++)
    {
	if (!alphSwitchList[i].episode)
	{
	    numswitches = index/2;
	    switchlist[index] = -1;
	    break;
	}
		
	if (alphSwitchList[i].episode <= episode)
	{
#if 0	// UNUSED - debug?
	    int		value;
			
	    if (R_CheckTextureNumForName(alphSwitchList[i].name1) < 0)
	    {
		I_Error("Can't find switch texture '%s'!",
			alphSwitchList[i].name1);
		continue;
	    }
	    
	    value = R_TextureNumForName(alphSwitchList[i].name1);
#endif
	    switchlist[index++] = R_TextureNumForName(alphSwitchList[i].name1);
	    switchlist[index++] = R_TextureNumForName(alphSwitchList[i].name2);
	}
    }
}