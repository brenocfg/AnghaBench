#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_1__ vissprite_t ;
struct TYPE_9__ {int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; scalar_t__ maskedtexturecol; } ;
typedef  TYPE_2__ drawseg_t ;

/* Variables and functions */
 int /*<<< orphan*/  R_DrawPlayerSprites () ; 
 int /*<<< orphan*/  R_DrawSprite (TYPE_1__*) ; 
 int /*<<< orphan*/  R_RenderMaskedSegRange (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_SortVisSprites () ; 
 TYPE_2__* drawsegs ; 
 TYPE_2__* ds_p ; 
 int /*<<< orphan*/  viewangleoffset ; 
 scalar_t__ vissprite_p ; 
 scalar_t__ vissprites ; 
 TYPE_1__ vsprsortedhead ; 

void R_DrawMasked (void)
{
    vissprite_t*	spr;
    drawseg_t*		ds;
	
    R_SortVisSprites ();

    if (vissprite_p > vissprites)
    {
	// draw all vissprites back to front
	for (spr = vsprsortedhead.next ;
	     spr != &vsprsortedhead ;
	     spr=spr->next)
	{
	    
	    R_DrawSprite (spr);
	}
    }
    
    // render any remaining masked mid textures
    for (ds=ds_p-1 ; ds >= drawsegs ; ds--)
	if (ds->maskedtexturecol)
	    R_RenderMaskedSegRange (ds, ds->x1, ds->x2);
    
    // draw the psprites on top of everything
    //  but does not draw on side views
    if (!viewangleoffset)		
	R_DrawPlayerSprites ();
}