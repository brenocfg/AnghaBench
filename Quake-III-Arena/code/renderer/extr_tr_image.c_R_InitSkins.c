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
struct TYPE_6__ {int numSurfaces; int /*<<< orphan*/  shader; struct TYPE_6__** surfaces; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ skin_t ;
struct TYPE_8__ {TYPE_1__* (* Hunk_Alloc ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int numSkins; int /*<<< orphan*/  defaultShader; TYPE_1__** skins; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  h_low ; 
 TYPE_5__ ri ; 
 TYPE_1__* stub1 (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* stub2 (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ tr ; 

void	R_InitSkins( void ) {
	skin_t		*skin;

	tr.numSkins = 1;

	// make the default skin have all default shaders
	skin = tr.skins[0] = ri.Hunk_Alloc( sizeof( skin_t ), h_low );
	Q_strncpyz( skin->name, "<default skin>", sizeof( skin->name )  );
	skin->numSurfaces = 1;
	skin->surfaces[0] = ri.Hunk_Alloc( sizeof( *skin->surfaces ), h_low );
	skin->surfaces[0]->shader = tr.defaultShader;
}