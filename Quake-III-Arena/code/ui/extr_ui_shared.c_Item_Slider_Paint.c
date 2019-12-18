#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  double* vec4_t ;
struct TYPE_16__ {double* focusColor; } ;
typedef  TYPE_5__ menuDef_t ;
struct TYPE_13__ {float y; float x; } ;
struct TYPE_14__ {int flags; TYPE_2__ rect; int /*<<< orphan*/  foreColor; } ;
struct TYPE_12__ {int x; int w; } ;
struct TYPE_17__ {TYPE_3__ window; TYPE_1__ textRect; scalar_t__ text; scalar_t__ cvar; scalar_t__ parent; } ;
typedef  TYPE_6__ itemDef_t ;
struct TYPE_15__ {int /*<<< orphan*/  sliderThumb; int /*<<< orphan*/  sliderBar; } ;
struct TYPE_11__ {float (* getCVarValue ) (scalar_t__) ;int realTime; TYPE_4__ Assets; int /*<<< orphan*/  (* drawHandlePic ) (float,float,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setColor ) (double*) ;} ;

/* Variables and functions */
 TYPE_10__* DC ; 
 float Item_Slider_ThumbPosition (TYPE_6__*) ; 
 int /*<<< orphan*/  Item_Text_Paint (TYPE_6__*) ; 
 int /*<<< orphan*/  LerpColor (double*,double*,double*,double) ; 
 int PULSE_DIVISOR ; 
 int /*<<< orphan*/  SLIDER_HEIGHT ; 
 int /*<<< orphan*/  SLIDER_THUMB_HEIGHT ; 
 int SLIDER_THUMB_WIDTH ; 
 int SLIDER_WIDTH ; 
 int WINDOW_HASFOCUS ; 
 int /*<<< orphan*/  memcpy (double**,int /*<<< orphan*/ *,int) ; 
 double sin (int) ; 
 float stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (double*) ; 
 int /*<<< orphan*/  stub3 (float,float,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (float,float,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Item_Slider_Paint(itemDef_t *item) {
	vec4_t newColor, lowLight;
	float x, y, value;
	menuDef_t *parent = (menuDef_t*)item->parent;

	value = (item->cvar) ? DC->getCVarValue(item->cvar) : 0;

	if (item->window.flags & WINDOW_HASFOCUS) {
		lowLight[0] = 0.8 * parent->focusColor[0]; 
		lowLight[1] = 0.8 * parent->focusColor[1]; 
		lowLight[2] = 0.8 * parent->focusColor[2]; 
		lowLight[3] = 0.8 * parent->focusColor[3]; 
		LerpColor(parent->focusColor,lowLight,newColor,0.5+0.5*sin(DC->realTime / PULSE_DIVISOR));
	} else {
		memcpy(&newColor, &item->window.foreColor, sizeof(vec4_t));
	}

	y = item->window.rect.y;
	if (item->text) {
		Item_Text_Paint(item);
		x = item->textRect.x + item->textRect.w + 8;
	} else {
		x = item->window.rect.x;
	}
	DC->setColor(newColor);
	DC->drawHandlePic( x, y, SLIDER_WIDTH, SLIDER_HEIGHT, DC->Assets.sliderBar );

	x = Item_Slider_ThumbPosition(item);
	DC->drawHandlePic( x - (SLIDER_THUMB_WIDTH / 2), y - 2, SLIDER_THUMB_WIDTH, SLIDER_THUMB_HEIGHT, DC->Assets.sliderThumb );

}