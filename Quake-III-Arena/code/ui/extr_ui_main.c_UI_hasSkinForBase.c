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
typedef  int /*<<< orphan*/  test ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  FS_READ ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ trap_FS_FOpenFile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

qboolean UI_hasSkinForBase(const char *base, const char *team) {
	char	test[1024];
	
	Com_sprintf( test, sizeof( test ), "models/players/%s/%s/lower_default.skin", base, team );

	if (trap_FS_FOpenFile(test, 0, FS_READ)) {
		return qtrue;
	}
	Com_sprintf( test, sizeof( test ), "models/players/characters/%s/%s/lower_default.skin", base, team );

	if (trap_FS_FOpenFile(test, 0, FS_READ)) {
		return qtrue;
	}
	return qfalse;
}