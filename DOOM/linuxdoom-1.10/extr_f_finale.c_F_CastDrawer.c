#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* lump; scalar_t__* flip; } ;
typedef  TYPE_1__ spriteframe_t ;
struct TYPE_7__ {TYPE_1__* spriteframes; } ;
typedef  TYPE_2__ spritedef_t ;
typedef  int /*<<< orphan*/  patch_t ;
typedef  scalar_t__ boolean ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {size_t sprite; size_t frame; } ;

/* Variables and functions */
 size_t FF_FRAMEMASK ; 
 int /*<<< orphan*/  F_CastPrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  V_DrawPatch (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_DrawPatchFlipped (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * W_CacheLumpName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * W_CacheLumpNum (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t castnum ; 
 TYPE_5__* castorder ; 
 TYPE_4__* caststate ; 
 scalar_t__ firstspritelump ; 
 TYPE_2__* sprites ; 

void F_CastDrawer (void)
{
    spritedef_t*	sprdef;
    spriteframe_t*	sprframe;
    int			lump;
    boolean		flip;
    patch_t*		patch;
    
    // erase the entire screen to a background
    V_DrawPatch (0,0,0, W_CacheLumpName ("BOSSBACK", PU_CACHE));

    F_CastPrint (castorder[castnum].name);
    
    // draw the current frame in the middle of the screen
    sprdef = &sprites[caststate->sprite];
    sprframe = &sprdef->spriteframes[ caststate->frame & FF_FRAMEMASK];
    lump = sprframe->lump[0];
    flip = (boolean)sprframe->flip[0];
			
    patch = W_CacheLumpNum (lump+firstspritelump, PU_CACHE);
    if (flip)
	V_DrawPatchFlipped (160,170,0,patch);
    else
	V_DrawPatch (160,170,0,patch);
}