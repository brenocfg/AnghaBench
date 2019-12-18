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
struct TYPE_2__ {scalar_t__* binding; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  Key_KeynumToString (int) ; 
 TYPE_1__* keys ; 

void Key_Bindlist_f( void ) {
	int		i;

	for ( i = 0 ; i < 256 ; i++ ) {
		if ( keys[i].binding && keys[i].binding[0] ) {
			Com_Printf( "%s \"%s\"\n", Key_KeynumToString(i), keys[i].binding );
		}
	}
}