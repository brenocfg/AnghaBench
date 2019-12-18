#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_7__ {int /*<<< orphan*/  rect; } ;
struct TYPE_8__ {int /*<<< orphan*/  cvar; TYPE_1__ window; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* setBinding ) (int,char*) ;int /*<<< orphan*/  cursory; int /*<<< orphan*/  cursorx; } ;
struct TYPE_9__ {int bind1; int bind2; } ;

/* Variables and functions */
 int BindingIDFromName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Controls_SetConfig (scalar_t__) ; 
 TYPE_6__* DC ; 
#define  K_BACKSPACE 129 
 int K_CHAR_FLAG ; 
 int K_ENTER ; 
#define  K_ESCAPE 128 
 int K_MOUSE1 ; 
 scalar_t__ Rect_ContainsPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_bindCount ; 
 TYPE_2__* g_bindItem ; 
 TYPE_3__* g_bindings ; 
 scalar_t__ g_waitingForKey ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  stub1 (int,char*) ; 
 int /*<<< orphan*/  stub2 (int,char*) ; 
 int /*<<< orphan*/  stub3 (int,char*) ; 
 int /*<<< orphan*/  stub4 (int,char*) ; 

qboolean Item_Bind_HandleKey(itemDef_t *item, int key, qboolean down) {
	int			id;
	int			i;

	if (Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory) && !g_waitingForKey)
	{
		if (down && (key == K_MOUSE1 || key == K_ENTER)) {
			g_waitingForKey = qtrue;
			g_bindItem = item;
		}
		return qtrue;
	}
	else
	{
		if (!g_waitingForKey || g_bindItem == NULL) {
			return qtrue;
		}

		if (key & K_CHAR_FLAG) {
			return qtrue;
		}

		switch (key)
		{
			case K_ESCAPE:
				g_waitingForKey = qfalse;
				return qtrue;
	
			case K_BACKSPACE:
				id = BindingIDFromName(item->cvar);
				if (id != -1) {
					g_bindings[id].bind1 = -1;
					g_bindings[id].bind2 = -1;
				}
				Controls_SetConfig(qtrue);
				g_waitingForKey = qfalse;
				g_bindItem = NULL;
				return qtrue;

			case '`':
				return qtrue;
		}
	}

	if (key != -1)
	{

		for (i=0; i < g_bindCount; i++)
		{

			if (g_bindings[i].bind2 == key) {
				g_bindings[i].bind2 = -1;
			}

			if (g_bindings[i].bind1 == key)
			{
				g_bindings[i].bind1 = g_bindings[i].bind2;
				g_bindings[i].bind2 = -1;
			}
		}
	}


	id = BindingIDFromName(item->cvar);

	if (id != -1) {
		if (key == -1) {
			if( g_bindings[id].bind1 != -1 ) {
				DC->setBinding( g_bindings[id].bind1, "" );
				g_bindings[id].bind1 = -1;
			}
			if( g_bindings[id].bind2 != -1 ) {
				DC->setBinding( g_bindings[id].bind2, "" );
				g_bindings[id].bind2 = -1;
			}
		}
		else if (g_bindings[id].bind1 == -1) {
			g_bindings[id].bind1 = key;
		}
		else if (g_bindings[id].bind1 != key && g_bindings[id].bind2 == -1) {
			g_bindings[id].bind2 = key;
		}
		else {
			DC->setBinding( g_bindings[id].bind1, "" );
			DC->setBinding( g_bindings[id].bind2, "" );
			g_bindings[id].bind1 = key;
			g_bindings[id].bind2 = -1;
		}						
	}

	Controls_SetConfig(qtrue);	
	g_waitingForKey = qfalse;

	return qtrue;
}