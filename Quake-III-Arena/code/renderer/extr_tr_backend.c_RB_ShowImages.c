#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float uploadWidth; float uploadHeight; } ;
typedef  TYPE_1__ image_t ;
struct TYPE_13__ {int /*<<< orphan*/  projection2D; } ;
struct TYPE_12__ {int vidWidth; int vidHeight; } ;
struct TYPE_11__ {int integer; } ;
struct TYPE_10__ {int (* Milliseconds ) () ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_9__ {int numImages; TYPE_1__** images; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_Bind (TYPE_1__*) ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  RB_SetGL2D () ; 
 TYPE_6__ backEnd ; 
 TYPE_5__ glConfig ; 
 int /*<<< orphan*/  qglBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnd () ; 
 int /*<<< orphan*/  qglFinish () ; 
 int /*<<< orphan*/  qglTexCoord2f (int,int) ; 
 int /*<<< orphan*/  qglVertex2f (float,float) ; 
 TYPE_4__* r_showImages ; 
 TYPE_3__ ri ; 
 int stub1 () ; 
 int stub2 () ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ tr ; 

void RB_ShowImages( void ) {
	int		i;
	image_t	*image;
	float	x, y, w, h;
	int		start, end;

	if ( !backEnd.projection2D ) {
		RB_SetGL2D();
	}

	qglClear( GL_COLOR_BUFFER_BIT );

	qglFinish();

	start = ri.Milliseconds();

	for ( i=0 ; i<tr.numImages ; i++ ) {
		image = tr.images[i];

		w = glConfig.vidWidth / 20;
		h = glConfig.vidHeight / 15;
		x = i % 20 * w;
		y = i / 20 * h;

		// show in proportional size in mode 2
		if ( r_showImages->integer == 2 ) {
			w *= image->uploadWidth / 512.0f;
			h *= image->uploadHeight / 512.0f;
		}

		GL_Bind( image );
		qglBegin (GL_QUADS);
		qglTexCoord2f( 0, 0 );
		qglVertex2f( x, y );
		qglTexCoord2f( 1, 0 );
		qglVertex2f( x + w, y );
		qglTexCoord2f( 1, 1 );
		qglVertex2f( x + w, y + h );
		qglTexCoord2f( 0, 1 );
		qglVertex2f( x, y + h );
		qglEnd();
	}

	qglFinish();

	end = ri.Milliseconds();
	ri.Printf( PRINT_ALL, "%i msec to draw all images\n", end - start );

}