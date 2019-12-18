#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ sfxHandle_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_LOCAL_SOUND ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_strrchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ S_RegisterSound (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_StartLocalSound (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 

void S_Play_f( void ) {
	int 		i;
	sfxHandle_t	h;
	char		name[256];
	
	i = 1;
	while ( i<Cmd_Argc() ) {
		if ( !Q_strrchr(Cmd_Argv(i), '.') ) {
			Com_sprintf( name, sizeof(name), "%s.wav", Cmd_Argv(1) );
		} else {
			Q_strncpyz( name, Cmd_Argv(i), sizeof(name) );
		}
		h = S_RegisterSound( name, qfalse );
		if( h ) {
			S_StartLocalSound( h, CHAN_LOCAL_SOUND );
		}
		i++;
	}
}