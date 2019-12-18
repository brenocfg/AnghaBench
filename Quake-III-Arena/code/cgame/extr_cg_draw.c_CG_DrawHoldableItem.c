#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* snap; } ;
struct TYPE_7__ {int /*<<< orphan*/  icon; } ;
struct TYPE_5__ {int* stats; } ;
struct TYPE_6__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_DrawPic (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_RegisterItemVisuals (int) ; 
 int ICON_SIZE ; 
 int SCREEN_HEIGHT ; 
 size_t STAT_HOLDABLE_ITEM ; 
 TYPE_4__ cg ; 
 TYPE_3__* cg_items ; 

__attribute__((used)) static void CG_DrawHoldableItem( void ) { 
	int		value;

	value = cg.snap->ps.stats[STAT_HOLDABLE_ITEM];
	if ( value ) {
		CG_RegisterItemVisuals( value );
		CG_DrawPic( 640-ICON_SIZE, (SCREEN_HEIGHT-ICON_SIZE)/2, ICON_SIZE, ICON_SIZE, cg_items[ value ].icon );
	}

}