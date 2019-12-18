#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  charSetShader; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DrawStretchPic ) (int,int,int /*<<< orphan*/ ,int,float,float,float,float,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int SMALLCHAR_HEIGHT ; 
 int /*<<< orphan*/  SMALLCHAR_WIDTH ; 
 TYPE_2__ cls ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ,int,float,float,float,float,int /*<<< orphan*/ ) ; 

void SCR_DrawSmallChar( int x, int y, int ch ) {
	int row, col;
	float frow, fcol;
	float size;

	ch &= 255;

	if ( ch == ' ' ) {
		return;
	}

	if ( y < -SMALLCHAR_HEIGHT ) {
		return;
	}

	row = ch>>4;
	col = ch&15;

	frow = row*0.0625;
	fcol = col*0.0625;
	size = 0.0625;

	re.DrawStretchPic( x, y, SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT,
					   fcol, frow, 
					   fcol + size, frow + size, 
					   cls.charSetShader );
}