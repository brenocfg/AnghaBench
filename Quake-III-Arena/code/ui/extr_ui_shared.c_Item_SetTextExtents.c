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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ownerDraw; } ;
struct TYPE_6__ {int w; int h; int /*<<< orphan*/  y; scalar_t__ x; } ;
struct TYPE_7__ {char const* text; scalar_t__ type; scalar_t__ textalignment; TYPE_3__ window; TYPE_1__ textRect; scalar_t__ textalignx; int /*<<< orphan*/  textaligny; int /*<<< orphan*/  textscale; scalar_t__ cvar; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_9__ {int (* textWidth ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* textHeight ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* getCVarString ) (scalar_t__,char*,int) ;scalar_t__ (* ownerDrawWidth ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_5__* DC ; 
 scalar_t__ ITEM_ALIGN_CENTER ; 
 scalar_t__ ITEM_ALIGN_RIGHT ; 
 scalar_t__ ITEM_TYPE_EDITFIELD ; 
 scalar_t__ ITEM_TYPE_OWNERDRAW ; 
 int /*<<< orphan*/  ToWindowCoords (scalar_t__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,char*,int) ; 
 int stub4 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub5 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub6 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Item_SetTextExtents(itemDef_t *item, int *width, int *height, const char *text) {
	const char *textPtr = (text) ? text : item->text;

	if (textPtr == NULL ) {
		return;
	}

	*width = item->textRect.w;
	*height = item->textRect.h;

	// keeps us from computing the widths and heights more than once
	if (*width == 0 || (item->type == ITEM_TYPE_OWNERDRAW && item->textalignment == ITEM_ALIGN_CENTER)) {
		int originalWidth = DC->textWidth(item->text, item->textscale, 0);

		if (item->type == ITEM_TYPE_OWNERDRAW && (item->textalignment == ITEM_ALIGN_CENTER || item->textalignment == ITEM_ALIGN_RIGHT)) {
			originalWidth += DC->ownerDrawWidth(item->window.ownerDraw, item->textscale);
		} else if (item->type == ITEM_TYPE_EDITFIELD && item->textalignment == ITEM_ALIGN_CENTER && item->cvar) {
			char buff[256];
			DC->getCVarString(item->cvar, buff, 256);
			originalWidth += DC->textWidth(buff, item->textscale, 0);
		}

		*width = DC->textWidth(textPtr, item->textscale, 0);
		*height = DC->textHeight(textPtr, item->textscale, 0);
		item->textRect.w = *width;
		item->textRect.h = *height;
		item->textRect.x = item->textalignx;
		item->textRect.y = item->textaligny;
		if (item->textalignment == ITEM_ALIGN_RIGHT) {
			item->textRect.x = item->textalignx - originalWidth;
		} else if (item->textalignment == ITEM_ALIGN_CENTER) {
			item->textRect.x = item->textalignx - originalWidth / 2;
		}

		ToWindowCoords(&item->textRect.x, &item->textRect.y, &item->window);
	}
}