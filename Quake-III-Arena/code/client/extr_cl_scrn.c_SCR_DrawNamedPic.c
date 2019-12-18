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
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* DrawStretchPic ) (float,float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* RegisterShader ) (char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SCR_AdjustFrom640 (float*,float*,float*,float*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (char const*) ; 
 int /*<<< orphan*/  stub2 (float,float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void SCR_DrawNamedPic( float x, float y, float width, float height, const char *picname ) {
	qhandle_t	hShader;

	assert( width != 0 );

	hShader = re.RegisterShader( picname );
	SCR_AdjustFrom640( &x, &y, &width, &height );
	re.DrawStretchPic( x, y, width, height, 0, 0, 1, 1, hShader );
}