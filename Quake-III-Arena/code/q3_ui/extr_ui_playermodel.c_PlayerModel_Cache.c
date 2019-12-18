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
struct TYPE_2__ {int nummodels; scalar_t__* modelnames; } ;

/* Variables and functions */
 int /*<<< orphan*/  PlayerModel_BuildList () ; 
 scalar_t__* playermodel_artlist ; 
 TYPE_1__ s_playermodel ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (scalar_t__) ; 

void PlayerModel_Cache( void )
{
	int	i;

	for( i = 0; playermodel_artlist[i]; i++ ) {
		trap_R_RegisterShaderNoMip( playermodel_artlist[i] );
	}

	PlayerModel_BuildList();
	for( i = 0; i < s_playermodel.nummodels; i++ ) {
		trap_R_RegisterShaderNoMip( s_playermodel.modelnames[i] );
	}
}