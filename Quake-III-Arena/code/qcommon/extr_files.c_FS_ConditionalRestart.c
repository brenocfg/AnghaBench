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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {scalar_t__ modified; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_Restart (int) ; 
 int fs_checksumFeed ; 
 TYPE_1__* fs_gamedirvar ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean FS_ConditionalRestart( int checksumFeed ) {
	if( fs_gamedirvar->modified || checksumFeed != fs_checksumFeed ) {
		FS_Restart( checksumFeed );
		return qtrue;
	}
	return qfalse;
}