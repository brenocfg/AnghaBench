#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  whiteImage; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_Bind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_LINES ; 
 int /*<<< orphan*/  qglBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglColor3f (int,int,int) ; 
 int /*<<< orphan*/  qglEnd () ; 
 int /*<<< orphan*/  qglLineWidth (int) ; 
 int /*<<< orphan*/  qglVertex3f (int,int,int) ; 
 TYPE_1__ tr ; 

void RB_SurfaceAxis( void ) {
	GL_Bind( tr.whiteImage );
	qglLineWidth( 3 );
	qglBegin( GL_LINES );
	qglColor3f( 1,0,0 );
	qglVertex3f( 0,0,0 );
	qglVertex3f( 16,0,0 );
	qglColor3f( 0,1,0 );
	qglVertex3f( 0,0,0 );
	qglVertex3f( 0,16,0 );
	qglColor3f( 0,0,1 );
	qglVertex3f( 0,0,0 );
	qglVertex3f( 0,0,16 );
	qglEnd();
	qglLineWidth( 1 );
}