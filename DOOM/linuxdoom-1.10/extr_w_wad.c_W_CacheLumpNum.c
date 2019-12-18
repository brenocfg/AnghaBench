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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*,int) ; 
 int /*<<< orphan*/  W_LumpLength (int) ; 
 int /*<<< orphan*/  W_ReadLump (int,void*) ; 
 int /*<<< orphan*/  Z_ChangeTag (void*,int) ; 
 int /*<<< orphan*/ * Z_Malloc (int /*<<< orphan*/ ,int,void**) ; 
 void** lumpcache ; 
 unsigned int numlumps ; 

void*
W_CacheLumpNum
( int		lump,
  int		tag )
{
    byte*	ptr;

    if ((unsigned)lump >= numlumps)
	I_Error ("W_CacheLumpNum: %i >= numlumps",lump);
		
    if (!lumpcache[lump])
    {
	// read the lump in
	
	//printf ("cache miss on lump %i\n",lump);
	ptr = Z_Malloc (W_LumpLength (lump), tag, &lumpcache[lump]);
	W_ReadLump (lump, lumpcache[lump]);
    }
    else
    {
	//printf ("cache hit on lump %i\n",lump);
	Z_ChangeTag (lumpcache[lump],tag);
    }
	
    return lumpcache[lump];
}