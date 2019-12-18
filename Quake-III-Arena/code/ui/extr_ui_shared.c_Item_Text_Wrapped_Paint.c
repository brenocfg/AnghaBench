#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_7__ {float x; float y; } ;
struct TYPE_8__ {char* text; int /*<<< orphan*/  textStyle; int /*<<< orphan*/  textscale; TYPE_1__ textRect; int /*<<< orphan*/ * cvar; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* drawText ) (float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* getCVarString ) (int /*<<< orphan*/ *,char*,int) ;} ;

/* Variables and functions */
 TYPE_6__* DC ; 
 int /*<<< orphan*/  Item_SetTextExtents (TYPE_2__*,int*,int*,char const*) ; 
 int /*<<< orphan*/  Item_TextColor (TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub2 (float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Item_Text_Wrapped_Paint(itemDef_t *item) {
	char text[1024];
	const char *p, *start, *textPtr;
	char buff[1024];
	int width, height;
	float x, y;
	vec4_t color;

	// now paint the text and/or any optional images
	// default to left

	if (item->text == NULL) {
		if (item->cvar == NULL) {
			return;
		}
		else {
			DC->getCVarString(item->cvar, text, sizeof(text));
			textPtr = text;
		}
	}
	else {
		textPtr = item->text;
	}
	if (*textPtr == '\0') {
		return;
	}

	Item_TextColor(item, &color);
	Item_SetTextExtents(item, &width, &height, textPtr);

	x = item->textRect.x;
	y = item->textRect.y;
	start = textPtr;
	p = strchr(textPtr, '\r');
	while (p && *p) {
		strncpy(buff, start, p-start+1);
		buff[p-start] = '\0';
		DC->drawText(x, y, item->textscale, color, buff, 0, 0, item->textStyle);
		y += height + 5;
		start += p - start + 1;
		p = strchr(p+1, '\r');
	}
	DC->drawText(x, y, item->textscale, color, start, 0, 0, item->textStyle);
}