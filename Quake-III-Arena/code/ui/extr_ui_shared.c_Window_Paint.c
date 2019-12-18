#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec4_t ;
struct TYPE_6__ {int x; int y; int h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ rectDef_t ;
struct TYPE_7__ {scalar_t__ style; scalar_t__ border; int borderSize; int flags; double* backColor; double* foreColor; int cinematic; double* borderColor; TYPE_1__ rect; int /*<<< orphan*/  cinematicName; int /*<<< orphan*/  background; int /*<<< orphan*/  nextTime; } ;
typedef  TYPE_2__ Window ;
struct TYPE_8__ {int (* playCinematic ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* setColor ) (double*) ;int /*<<< orphan*/  (* drawSides ) (int,int,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* drawTopBottom ) (int,int,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* drawRect ) (int,int,int /*<<< orphan*/ ,int,int,double*) ;int /*<<< orphan*/  (* drawCinematic ) (int,int,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* runCinematicFrame ) (int) ;int /*<<< orphan*/  (* fillRect ) (int,int,int /*<<< orphan*/ ,int,double*) ;int /*<<< orphan*/  (* getTeamColor ) (double**) ;int /*<<< orphan*/  (* drawHandlePic ) (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_5__* DC ; 
 int /*<<< orphan*/  Fade (int*,double*,float,int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  GradientBar_Paint (TYPE_1__*,double*) ; 
 scalar_t__ WINDOW_BORDER_FULL ; 
 scalar_t__ WINDOW_BORDER_HORZ ; 
 scalar_t__ WINDOW_BORDER_KCGRADIENT ; 
 scalar_t__ WINDOW_BORDER_VERT ; 
 int WINDOW_FORECOLORSET ; 
 scalar_t__ WINDOW_STYLE_CINEMATIC ; 
 scalar_t__ WINDOW_STYLE_FILLED ; 
 scalar_t__ WINDOW_STYLE_GRADIENT ; 
 scalar_t__ WINDOW_STYLE_SHADER ; 
 scalar_t__ WINDOW_STYLE_TEAMCOLOR ; 
 scalar_t__ debugMode ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ,int,int,double*) ; 
 int /*<<< orphan*/  stub10 (int,int,int /*<<< orphan*/ ,int,double*) ; 
 int stub11 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub12 (int) ; 
 int /*<<< orphan*/  stub13 (int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub14 (int,int,int /*<<< orphan*/ ,int,int,double*) ; 
 int /*<<< orphan*/  stub15 (int,int,int /*<<< orphan*/ ,int,int,double*) ; 
 int /*<<< orphan*/  stub16 (double*) ; 
 int /*<<< orphan*/  stub17 (int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub18 (double*) ; 
 int /*<<< orphan*/  stub19 (double*) ; 
 int /*<<< orphan*/  stub2 (double*) ; 
 int /*<<< orphan*/  stub20 (int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub21 (double*) ; 
 int /*<<< orphan*/  stub3 (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (double*) ; 
 int /*<<< orphan*/  stub5 (int,int,int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  stub6 (double*) ; 
 int /*<<< orphan*/  stub7 (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (double*) ; 
 int /*<<< orphan*/  stub9 (double**) ; 

void Window_Paint(Window *w, float fadeAmount, float fadeClamp, float fadeCycle) {
  //float bordersize = 0;
  vec4_t color;
  rectDef_t fillRect = w->rect;


  if (debugMode) {
    color[0] = color[1] = color[2] = color[3] = 1;
    DC->drawRect(w->rect.x, w->rect.y, w->rect.w, w->rect.h, 1, color);
  }

  if (w == NULL || (w->style == 0 && w->border == 0)) {
    return;
  }

  if (w->border != 0) {
    fillRect.x += w->borderSize;
    fillRect.y += w->borderSize;
    fillRect.w -= w->borderSize + 1;
    fillRect.h -= w->borderSize + 1;
  }

  if (w->style == WINDOW_STYLE_FILLED) {
    // box, but possible a shader that needs filled
		if (w->background) {
		  Fade(&w->flags, &w->backColor[3], fadeClamp, &w->nextTime, fadeCycle, qtrue, fadeAmount);
      DC->setColor(w->backColor);
	    DC->drawHandlePic(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->background);
		  DC->setColor(NULL);
		} else {
	    DC->fillRect(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->backColor);
		}
  } else if (w->style == WINDOW_STYLE_GRADIENT) {
    GradientBar_Paint(&fillRect, w->backColor);
    // gradient bar
  } else if (w->style == WINDOW_STYLE_SHADER) {
    if (w->flags & WINDOW_FORECOLORSET) {
      DC->setColor(w->foreColor);
    }
    DC->drawHandlePic(fillRect.x, fillRect.y, fillRect.w, fillRect.h, w->background);
    DC->setColor(NULL);
  } else if (w->style == WINDOW_STYLE_TEAMCOLOR) {
    if (DC->getTeamColor) {
      DC->getTeamColor(&color);
      DC->fillRect(fillRect.x, fillRect.y, fillRect.w, fillRect.h, color);
    }
  } else if (w->style == WINDOW_STYLE_CINEMATIC) {
		if (w->cinematic == -1) {
			w->cinematic = DC->playCinematic(w->cinematicName, fillRect.x, fillRect.y, fillRect.w, fillRect.h);
			if (w->cinematic == -1) {
				w->cinematic = -2;
			}
		} 
		if (w->cinematic >= 0) {
	    DC->runCinematicFrame(w->cinematic);
			DC->drawCinematic(w->cinematic, fillRect.x, fillRect.y, fillRect.w, fillRect.h);
		}
  }

  if (w->border == WINDOW_BORDER_FULL) {
    // full
    // HACK HACK HACK
    if (w->style == WINDOW_STYLE_TEAMCOLOR) {
      if (color[0] > 0) { 
        // red
        color[0] = 1;
        color[1] = color[2] = .5;

      } else {
        color[2] = 1;
        color[0] = color[1] = .5;
      }
      color[3] = 1;
      DC->drawRect(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->borderSize, color);
    } else {
      DC->drawRect(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->borderSize, w->borderColor);
    }
  } else if (w->border == WINDOW_BORDER_HORZ) {
    // top/bottom
    DC->setColor(w->borderColor);
    DC->drawTopBottom(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->borderSize);
  	DC->setColor( NULL );
  } else if (w->border == WINDOW_BORDER_VERT) {
    // left right
    DC->setColor(w->borderColor);
    DC->drawSides(w->rect.x, w->rect.y, w->rect.w, w->rect.h, w->borderSize);
  	DC->setColor( NULL );
  } else if (w->border == WINDOW_BORDER_KCGRADIENT) {
    // this is just two gradient bars along each horz edge
    rectDef_t r = w->rect;
    r.h = w->borderSize;
    GradientBar_Paint(&r, w->borderColor);
    r.y = w->rect.y + w->rect.h - 1;
    GradientBar_Paint(&r, w->borderColor);
  }

}