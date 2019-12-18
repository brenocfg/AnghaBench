#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  rect; } ;
struct TYPE_6__ {scalar_t__ cvar; TYPE_1__ window; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* getCVarValue ) (scalar_t__) ;int /*<<< orphan*/  (* setCVar ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cursory; int /*<<< orphan*/  cursorx; } ;

/* Variables and functions */
 TYPE_4__* DC ; 
 int K_ENTER ; 
 int K_MOUSE1 ; 
 int K_MOUSE2 ; 
 int K_MOUSE3 ; 
 scalar_t__ Rect_ContainsPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WINDOW_HASFOCUS ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  va (char*,int) ; 

qboolean Item_YesNo_HandleKey(itemDef_t *item, int key) {

  if (Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory) && item->window.flags & WINDOW_HASFOCUS && item->cvar) {
		if (key == K_MOUSE1 || key == K_ENTER || key == K_MOUSE2 || key == K_MOUSE3) {
	    DC->setCVar(item->cvar, va("%i", !DC->getCVarValue(item->cvar)));
		  return qtrue;
		}
  }

  return qfalse;

}